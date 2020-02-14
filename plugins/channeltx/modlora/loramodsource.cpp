///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#include <QDebug>

#include "loramodsource.h"

const int LoRaModSource::m_levelNbSamples = 480; // every 10ms

LoRaModSource::LoRaModSource() :
    m_channelSampleRate(48000),
    m_channelFrequencyOffset(0),
    m_downChirps(nullptr),
    m_upChirps(nullptr),
    m_phaseIncrements(nullptr),
    m_modPhasor(0.0f),
	m_levelCalcCount(0),
	m_peakLevel(0.0f),
	m_levelSum(0.0f),
    m_repeatCount(0),
    m_active(false)
{
	m_magsq = 0.0;

    initSF(m_settings.m_spreadFactor);
    initTest(m_settings.m_spreadFactor, m_settings.m_deBits);
    reset();
    applySettings(m_settings, true);
    applyChannelSettings(m_channelSampleRate, m_channelFrequencyOffset, true);
}

LoRaModSource::~LoRaModSource()
{
    delete[] m_downChirps;
    delete[] m_upChirps;
    delete[] m_phaseIncrements;
}

void LoRaModSource::initSF(unsigned int sf)
{
    if (m_downChirps) {
        delete[] m_downChirps;
    }
    if (m_upChirps) {
        delete[] m_upChirps;
    }

    m_fftLength = 1 << sf;
    m_state = LoRaStateIdle;
    m_quarterSamples = (m_fftLength/4)*LoRaModSettings::oversampling;
    m_downChirps = new Complex[2*m_fftLength*LoRaModSettings::oversampling]; // Each table is 2 chirps long to allow use from arbitrary offsets.
    m_upChirps = new Complex[2*m_fftLength*LoRaModSettings::oversampling];

    float halfAngle = M_PI/LoRaModSettings::oversampling;
    float phase = -halfAngle;
    double accumulator = 0;

    for (int i = 0; i < 2*m_fftLength*LoRaModSettings::oversampling; i++)
    {
        accumulator = fmod(accumulator + phase, 2*M_PI);
        m_downChirps[i] = Complex(std::conj(std::polar(0.891235351562 * SDR_TX_SCALED, accumulator))); // -1 dB
        m_upChirps[i] = Complex(std::polar(0.891235351562 * SDR_TX_SCALED, accumulator));
        phase += (2*halfAngle) / (m_fftLength*LoRaModSettings::oversampling);
        phase = phase > halfAngle ? phase - 2.0*halfAngle : phase;
    }

    if (m_phaseIncrements) {
        delete[] m_phaseIncrements;
    }

    m_phaseIncrements = new double[2*m_fftLength*LoRaModSettings::oversampling];
    phase = -halfAngle;

    for (int i = 0; i < m_fftLength*LoRaModSettings::oversampling; i++)
    {
        m_phaseIncrements[i] = phase;
        phase += (2*halfAngle) / (m_fftLength*LoRaModSettings::oversampling);
    }

    std::copy(
        m_phaseIncrements,
        m_phaseIncrements+m_fftLength*LoRaModSettings::oversampling,
        m_phaseIncrements+m_fftLength*LoRaModSettings::oversampling
    );
}

void LoRaModSource::initTest(unsigned int sf, unsigned int deBits)
{
    unsigned int fftLength = 1<<sf;
    unsigned int symbolRange = fftLength/(1<<deBits);
    m_symbols.clear();

    for (unsigned int seq = 0; seq < 1; seq++)
    {
        for (unsigned int symbol = 0; symbol < symbolRange; symbol += symbolRange/4)
        {
            m_symbols.push_back(symbol);
            m_symbols.push_back(symbol+1);
        }
    }
}

void LoRaModSource::reset()
{
    m_chirp = 0;
    m_chirp0 = 0;
    m_sampleCounter = 0;
    m_fftCounter = 0;
    m_chirpCount = 0;
}

void LoRaModSource::pull(SampleVector::iterator begin, unsigned int nbSamples)
{
    std::for_each(
        begin,
        begin + nbSamples,
        [this](Sample& s) {
            pullOne(s);
        }
    );
}

void LoRaModSource::pullOne(Sample& sample)
{
	if (m_settings.m_channelMute)
	{
		sample.m_real = 0.0f;
		sample.m_imag = 0.0f;
        m_magsq = 0.0;
		return;
	}

	Complex ci;

    if (m_interpolatorDistance > 1.0f) // decimate
    {
    	modulateSample();

        while (!m_interpolator.decimate(&m_interpolatorDistanceRemain, m_modSample, &ci))
        {
        	modulateSample();
        }
    }
    else
    {
        if (m_interpolator.interpolate(&m_interpolatorDistanceRemain, m_modSample, &ci))
        {
        	modulateSample();
        }
    }

    m_interpolatorDistanceRemain += m_interpolatorDistance;

    ci *= m_carrierNco.nextIQ(); // shift to carrier frequency

    if (!(m_state == LoRaStateIdle))
    {
        double magsq = std::norm(ci);
        magsq /= (SDR_TX_SCALED*SDR_TX_SCALED);
        m_movingAverage(magsq);
        m_magsq = m_movingAverage.asDouble();
    }

	sample.m_real = (FixReal) ci.real();
	sample.m_imag = (FixReal) ci.imag();
}

void LoRaModSource::modulateSample()
{
    if (m_state == LoRaStateIdle)
    {
        m_modSample = Complex{0.0, 0.0};
        m_sampleCounter++;

        if (m_sampleCounter == m_quietSamples*LoRaModSettings::oversampling) // done with quiet time
        {
            m_chirp0 = 0;
            m_chirp = m_fftLength*LoRaModSettings::oversampling - 1;

            if (m_symbols.size() != 0) // some payload to transmit
            {
                if (m_settings.m_messageRepeat == 0) // infinite
                {
                    m_state = LoRaStatePreamble;
                    m_active = true;
                }
                else
                {
                    if (m_repeatCount != 0)
                    {
                        m_repeatCount--;
                        m_state = LoRaStatePreamble;
                        m_active = true;
                    }
                    else
                    {
                        m_active = false;
                    }
                }
            }
            else
            {
                m_active = false;
            }
        }
    }
    else if (m_state == LoRaStatePreamble)
    {
        // m_modSample = m_upChirps[m_chirp];
        m_modSample = Complex(std::polar(0.891235351562 * SDR_TX_SCALED, m_modPhasor));
        m_modPhasor += m_phaseIncrements[m_chirp];
        m_fftCounter++;

        if (m_fftCounter == m_fftLength*LoRaModSettings::oversampling)
        {
            m_chirpCount++;
            m_fftCounter = 0;

            if (m_chirpCount == m_settings.m_preambleChirps)
            {
                m_chirpCount = 0;
                m_chirp0 = ((m_settings.m_syncWord >> ((1-m_chirpCount)*4)) & 0xf)*8;
                m_chirp = (m_chirp0 + m_fftLength)*LoRaModSettings::oversampling - 1;
                m_fftCounter = 0;
                m_state = LoRaStateSyncWord;
            }
        }
    }
    else if (m_state == LoRaStateSyncWord)
    {
        // m_modSample = m_upChirps[m_chirp];
        m_modSample = Complex(std::polar(0.891235351562 * SDR_TX_SCALED, m_modPhasor));
        m_modPhasor += m_phaseIncrements[m_chirp];
        m_fftCounter++;

        if (m_fftCounter == m_fftLength*LoRaModSettings::oversampling)
        {
            m_chirpCount++;
            m_chirp0 = ((m_settings.m_syncWord >> ((1-m_chirpCount)*4)) & 0xf)*8;
            m_chirp = (m_chirp0 + m_fftLength)*LoRaModSettings::oversampling - 1;
            m_fftCounter = 0;

            if (m_chirpCount == 2)
            {
                m_sampleCounter = 0;
                m_chirpCount = 0;
                m_chirp0 = 0;
                m_chirp = m_fftLength*LoRaModSettings::oversampling - 1;
                m_state = LoRaStateSFD;
            }
        }
    }
    else if (m_state == LoRaStateSFD)
    {
        // m_modSample = m_downChirps[m_chirp];
        m_modSample = Complex(std::polar(0.891235351562 * SDR_TX_SCALED, m_modPhasor));
        int chirpIndex = m_fftLength*LoRaModSettings::oversampling - 1 - m_chirp;
        m_modPhasor += m_phaseIncrements[chirpIndex];
        m_fftCounter++;
        m_sampleCounter++;

        if (m_fftCounter == m_fftLength*LoRaModSettings::oversampling)
        {
            m_chirp0 = 0;
            m_chirp = m_fftLength*LoRaModSettings::oversampling - 1;
            m_fftCounter = 0;
        }

        if (m_sampleCounter == m_quarterSamples)
        {
            m_chirpCount++;
            m_sampleCounter = 0;
        }

        if (m_chirpCount == 9)
        {
            m_fftCounter = 0;
            m_chirpCount = 0;
            m_chirp0 = encodeSymbol(m_symbols[m_chirpCount]);
            m_chirp = (m_chirp0 + m_fftLength)*LoRaModSettings::oversampling - 1;
            m_state = LoRaStatePayload;
        }
    }
    else if (m_state == LoRaStatePayload)
    {
        // m_modSample = m_upChirps[m_chirp];
        m_modSample = Complex(std::polar(0.891235351562 * SDR_TX_SCALED, m_modPhasor));
        m_modPhasor += m_phaseIncrements[m_chirp];
        m_fftCounter++;

        if (m_fftCounter == m_fftLength*LoRaModSettings::oversampling)
        {
            m_chirpCount++;

            if (m_chirpCount == m_symbols.size())
            {
                reset();
                m_state = LoRaStateIdle;
            }
            else
            {
                m_chirp0 = encodeSymbol(m_symbols[m_chirpCount]);
                m_chirp = (m_chirp0 + m_fftLength)*LoRaModSettings::oversampling - 1;
                m_fftCounter = 0;
            }
        }
    }

    // limit phasor range to ]-pi,pi]
    if (m_modPhasor > M_PI) {
        m_modPhasor -= (2.0f * M_PI);
    }

    m_chirp++;

    if (m_chirp >= (m_chirp0 + m_fftLength)*LoRaModSettings::oversampling) {
        m_chirp = m_chirp0*LoRaModSettings::oversampling;
    }
}

unsigned int LoRaModSource::encodeSymbol(unsigned int symbol)
{
    if (m_settings.m_deBits == 0) {
        return symbol;
    }

    unsigned int deWidth = 1<<m_settings.m_deBits;
    unsigned int baseSymbol = symbol % (m_fftLength/deWidth); // symbols range control
    return deWidth*baseSymbol;
    // return deWidth*baseSymbol + (deWidth/2) - 1;
}

void LoRaModSource::processOneSample(Complex& ci)
{
}

void LoRaModSource::calculateLevel(Real& sample)
{
    if (m_levelCalcCount < m_levelNbSamples)
    {
        m_peakLevel = std::max(std::fabs(m_peakLevel), sample);
        m_levelSum += sample * sample;
        m_levelCalcCount++;
    }
    else
    {
        m_rmsLevel = sqrt(m_levelSum / m_levelNbSamples);
        m_peakLevelOut = m_peakLevel;
        m_peakLevel = 0.0f;
        m_levelSum = 0.0f;
        m_levelCalcCount = 0;
    }
}

void LoRaModSource::applySettings(const LoRaModSettings& settings, bool force)
{
    if ((settings.m_spreadFactor != m_settings.m_spreadFactor)
     || (settings.m_deBits != m_settings.m_deBits)
     || (settings.m_preambleChirps != m_settings.m_preambleChirps)|| force)
    {
        initSF(settings.m_spreadFactor);
        initTest(settings.m_spreadFactor, settings.m_deBits);
        reset();
    }

    if ((settings.m_quietMillis != m_settings.m_quietMillis) || force)
    {
        m_quietSamples = (m_bandwidth*settings.m_quietMillis) / 1000;
        reset();
    }

    if ((settings.m_messageRepeat != m_settings.m_messageRepeat) || force) {
        m_repeatCount = settings.m_messageRepeat;
    }

    m_settings = settings;
}

void LoRaModSource::applyChannelSettings(int channelSampleRate, int bandwidth, int channelFrequencyOffset, bool force)
{
    qDebug() << "LoRaModSource::applyChannelSettings:"
            << " channelSampleRate: " << channelSampleRate
            << " channelFrequencyOffset: " << channelFrequencyOffset
            << " bandwidth: " << bandwidth
            << " SR: " << bandwidth * LoRaModSettings::oversampling;

    if ((channelFrequencyOffset != m_channelFrequencyOffset)
     || (channelSampleRate != m_channelSampleRate) || force)
    {
        m_carrierNco.setFreq(channelFrequencyOffset, channelSampleRate);
    }

    if ((channelSampleRate != m_channelSampleRate)
     || (bandwidth != m_bandwidth) || force)
    {
        m_interpolatorDistanceRemain = 0;
        m_interpolatorConsumed = false;
        m_interpolatorDistance = (Real) (bandwidth*LoRaModSettings::oversampling) / (Real) channelSampleRate;
        m_interpolator.create(16, bandwidth, bandwidth / 2.2);
    }

    m_channelSampleRate = channelSampleRate;
    m_channelFrequencyOffset = channelFrequencyOffset;
    m_bandwidth = bandwidth;
    m_quietSamples = (bandwidth*m_settings.m_quietMillis) / 1000;
    m_state = LoRaStateIdle;
    reset();
}

void LoRaModSource::setSymbols(const std::vector<unsigned int>& symbols)
{
    m_symbols = symbols;
    qDebug("LoRaModSource::setSymbols: m_symbols: %lu", m_symbols.size());
    m_repeatCount = m_settings.m_messageRepeat;
    m_state = LoRaStateIdle; // first reset to idle
    reset();
    m_sampleCounter = m_quietSamples*LoRaModSettings::oversampling - 1; // start immediately
}
