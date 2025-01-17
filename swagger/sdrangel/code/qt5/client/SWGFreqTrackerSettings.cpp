/**
 * SDRangel
 * This is the web REST/JSON API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ (4.3+ in Windows) GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube    ---   Limitations and specifcities:    * In SDRangel GUI the first Rx device set cannot be deleted. Conversely the server starts with no device sets and its number of device sets can be reduced to zero by as many calls as necessary to /sdrangel/deviceset with DELETE method.   * Preset import and export from/to file is a server only feature.   * Device set focus is a GUI only feature.   * The following channels are not implemented (status 501 is returned): ATV and DATV demodulators, Channel Analyzer NG, LoRa demodulator   * The device settings and report structures contains only the sub-structure corresponding to the device type. The DeviceSettings and DeviceReport structures documented here shows all of them but only one will be or should be present at a time   * The channel settings and report structures contains only the sub-structure corresponding to the channel type. The ChannelSettings and ChannelReport structures documented here shows all of them but only one will be or should be present at a time    --- 
 *
 * OpenAPI spec version: 6.0.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */


#include "SWGFreqTrackerSettings.h"

#include "SWGHelpers.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

namespace SWGSDRangel {

SWGFreqTrackerSettings::SWGFreqTrackerSettings(QString* json) {
    init();
    this->fromJson(*json);
}

SWGFreqTrackerSettings::SWGFreqTrackerSettings() {
    input_frequency_offset = 0L;
    m_input_frequency_offset_isSet = false;
    rf_bandwidth = 0.0f;
    m_rf_bandwidth_isSet = false;
    log2_decim = 0;
    m_log2_decim_isSet = false;
    squelch = 0.0f;
    m_squelch_isSet = false;
    rgb_color = 0;
    m_rgb_color_isSet = false;
    title = nullptr;
    m_title_isSet = false;
    span_log2 = 0;
    m_span_log2_isSet = false;
    alpha_ema = 0.0f;
    m_alpha_ema_isSet = false;
    tracking = 0;
    m_tracking_isSet = false;
    tracker_type = 0;
    m_tracker_type_isSet = false;
    pll_psk_order = 0;
    m_pll_psk_order_isSet = false;
    rrc = 0;
    m_rrc_isSet = false;
    rrc_rolloff = 0;
    m_rrc_rolloff_isSet = false;
    squelch_gate = 0;
    m_squelch_gate_isSet = false;
    stream_index = 0;
    m_stream_index_isSet = false;
    use_reverse_api = 0;
    m_use_reverse_api_isSet = false;
    reverse_api_address = nullptr;
    m_reverse_api_address_isSet = false;
    reverse_api_port = 0;
    m_reverse_api_port_isSet = false;
    reverse_api_device_index = 0;
    m_reverse_api_device_index_isSet = false;
    reverse_api_channel_index = 0;
    m_reverse_api_channel_index_isSet = false;
    spectrum_config = nullptr;
    m_spectrum_config_isSet = false;
    channel_marker = nullptr;
    m_channel_marker_isSet = false;
    rollup_state = nullptr;
    m_rollup_state_isSet = false;
}

SWGFreqTrackerSettings::~SWGFreqTrackerSettings() {
    this->cleanup();
}

void
SWGFreqTrackerSettings::init() {
    input_frequency_offset = 0L;
    m_input_frequency_offset_isSet = false;
    rf_bandwidth = 0.0f;
    m_rf_bandwidth_isSet = false;
    log2_decim = 0;
    m_log2_decim_isSet = false;
    squelch = 0.0f;
    m_squelch_isSet = false;
    rgb_color = 0;
    m_rgb_color_isSet = false;
    title = new QString("");
    m_title_isSet = false;
    span_log2 = 0;
    m_span_log2_isSet = false;
    alpha_ema = 0.0f;
    m_alpha_ema_isSet = false;
    tracking = 0;
    m_tracking_isSet = false;
    tracker_type = 0;
    m_tracker_type_isSet = false;
    pll_psk_order = 0;
    m_pll_psk_order_isSet = false;
    rrc = 0;
    m_rrc_isSet = false;
    rrc_rolloff = 0;
    m_rrc_rolloff_isSet = false;
    squelch_gate = 0;
    m_squelch_gate_isSet = false;
    stream_index = 0;
    m_stream_index_isSet = false;
    use_reverse_api = 0;
    m_use_reverse_api_isSet = false;
    reverse_api_address = new QString("");
    m_reverse_api_address_isSet = false;
    reverse_api_port = 0;
    m_reverse_api_port_isSet = false;
    reverse_api_device_index = 0;
    m_reverse_api_device_index_isSet = false;
    reverse_api_channel_index = 0;
    m_reverse_api_channel_index_isSet = false;
    spectrum_config = new SWGGLSpectrum();
    m_spectrum_config_isSet = false;
    channel_marker = new SWGChannelMarker();
    m_channel_marker_isSet = false;
    rollup_state = new SWGRollupState();
    m_rollup_state_isSet = false;
}

void
SWGFreqTrackerSettings::cleanup() {





    if(title != nullptr) { 
        delete title;
    }










    if(reverse_api_address != nullptr) { 
        delete reverse_api_address;
    }



    if(spectrum_config != nullptr) { 
        delete spectrum_config;
    }
    if(channel_marker != nullptr) { 
        delete channel_marker;
    }
    if(rollup_state != nullptr) { 
        delete rollup_state;
    }
}

SWGFreqTrackerSettings*
SWGFreqTrackerSettings::fromJson(QString &json) {
    QByteArray array (json.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
    return this;
}

void
SWGFreqTrackerSettings::fromJsonObject(QJsonObject &pJson) {
    ::SWGSDRangel::setValue(&input_frequency_offset, pJson["inputFrequencyOffset"], "qint64", "");
    
    ::SWGSDRangel::setValue(&rf_bandwidth, pJson["rfBandwidth"], "float", "");
    
    ::SWGSDRangel::setValue(&log2_decim, pJson["log2Decim"], "qint32", "");
    
    ::SWGSDRangel::setValue(&squelch, pJson["squelch"], "float", "");
    
    ::SWGSDRangel::setValue(&rgb_color, pJson["rgbColor"], "qint32", "");
    
    ::SWGSDRangel::setValue(&title, pJson["title"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&span_log2, pJson["spanLog2"], "qint32", "");
    
    ::SWGSDRangel::setValue(&alpha_ema, pJson["alphaEMA"], "float", "");
    
    ::SWGSDRangel::setValue(&tracking, pJson["tracking"], "qint32", "");
    
    ::SWGSDRangel::setValue(&tracker_type, pJson["trackerType"], "qint32", "");
    
    ::SWGSDRangel::setValue(&pll_psk_order, pJson["pllPskOrder"], "qint32", "");
    
    ::SWGSDRangel::setValue(&rrc, pJson["rrc"], "qint32", "");
    
    ::SWGSDRangel::setValue(&rrc_rolloff, pJson["rrcRolloff"], "qint32", "");
    
    ::SWGSDRangel::setValue(&squelch_gate, pJson["squelchGate"], "qint32", "");
    
    ::SWGSDRangel::setValue(&stream_index, pJson["streamIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&use_reverse_api, pJson["useReverseAPI"], "qint32", "");
    
    ::SWGSDRangel::setValue(&reverse_api_address, pJson["reverseAPIAddress"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&reverse_api_port, pJson["reverseAPIPort"], "qint32", "");
    
    ::SWGSDRangel::setValue(&reverse_api_device_index, pJson["reverseAPIDeviceIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&reverse_api_channel_index, pJson["reverseAPIChannelIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&spectrum_config, pJson["spectrumConfig"], "SWGGLSpectrum", "SWGGLSpectrum");
    
    ::SWGSDRangel::setValue(&channel_marker, pJson["channelMarker"], "SWGChannelMarker", "SWGChannelMarker");
    
    ::SWGSDRangel::setValue(&rollup_state, pJson["rollupState"], "SWGRollupState", "SWGRollupState");
    
}

QString
SWGFreqTrackerSettings::asJson ()
{
    QJsonObject* obj = this->asJsonObject();

    QJsonDocument doc(*obj);
    QByteArray bytes = doc.toJson();
    delete obj;
    return QString(bytes);
}

QJsonObject*
SWGFreqTrackerSettings::asJsonObject() {
    QJsonObject* obj = new QJsonObject();
    if(m_input_frequency_offset_isSet){
        obj->insert("inputFrequencyOffset", QJsonValue(input_frequency_offset));
    }
    if(m_rf_bandwidth_isSet){
        obj->insert("rfBandwidth", QJsonValue(rf_bandwidth));
    }
    if(m_log2_decim_isSet){
        obj->insert("log2Decim", QJsonValue(log2_decim));
    }
    if(m_squelch_isSet){
        obj->insert("squelch", QJsonValue(squelch));
    }
    if(m_rgb_color_isSet){
        obj->insert("rgbColor", QJsonValue(rgb_color));
    }
    if(title != nullptr && *title != QString("")){
        toJsonValue(QString("title"), title, obj, QString("QString"));
    }
    if(m_span_log2_isSet){
        obj->insert("spanLog2", QJsonValue(span_log2));
    }
    if(m_alpha_ema_isSet){
        obj->insert("alphaEMA", QJsonValue(alpha_ema));
    }
    if(m_tracking_isSet){
        obj->insert("tracking", QJsonValue(tracking));
    }
    if(m_tracker_type_isSet){
        obj->insert("trackerType", QJsonValue(tracker_type));
    }
    if(m_pll_psk_order_isSet){
        obj->insert("pllPskOrder", QJsonValue(pll_psk_order));
    }
    if(m_rrc_isSet){
        obj->insert("rrc", QJsonValue(rrc));
    }
    if(m_rrc_rolloff_isSet){
        obj->insert("rrcRolloff", QJsonValue(rrc_rolloff));
    }
    if(m_squelch_gate_isSet){
        obj->insert("squelchGate", QJsonValue(squelch_gate));
    }
    if(m_stream_index_isSet){
        obj->insert("streamIndex", QJsonValue(stream_index));
    }
    if(m_use_reverse_api_isSet){
        obj->insert("useReverseAPI", QJsonValue(use_reverse_api));
    }
    if(reverse_api_address != nullptr && *reverse_api_address != QString("")){
        toJsonValue(QString("reverseAPIAddress"), reverse_api_address, obj, QString("QString"));
    }
    if(m_reverse_api_port_isSet){
        obj->insert("reverseAPIPort", QJsonValue(reverse_api_port));
    }
    if(m_reverse_api_device_index_isSet){
        obj->insert("reverseAPIDeviceIndex", QJsonValue(reverse_api_device_index));
    }
    if(m_reverse_api_channel_index_isSet){
        obj->insert("reverseAPIChannelIndex", QJsonValue(reverse_api_channel_index));
    }
    if((spectrum_config != nullptr) && (spectrum_config->isSet())){
        toJsonValue(QString("spectrumConfig"), spectrum_config, obj, QString("SWGGLSpectrum"));
    }
    if((channel_marker != nullptr) && (channel_marker->isSet())){
        toJsonValue(QString("channelMarker"), channel_marker, obj, QString("SWGChannelMarker"));
    }
    if((rollup_state != nullptr) && (rollup_state->isSet())){
        toJsonValue(QString("rollupState"), rollup_state, obj, QString("SWGRollupState"));
    }

    return obj;
}

qint64
SWGFreqTrackerSettings::getInputFrequencyOffset() {
    return input_frequency_offset;
}
void
SWGFreqTrackerSettings::setInputFrequencyOffset(qint64 input_frequency_offset) {
    this->input_frequency_offset = input_frequency_offset;
    this->m_input_frequency_offset_isSet = true;
}

float
SWGFreqTrackerSettings::getRfBandwidth() {
    return rf_bandwidth;
}
void
SWGFreqTrackerSettings::setRfBandwidth(float rf_bandwidth) {
    this->rf_bandwidth = rf_bandwidth;
    this->m_rf_bandwidth_isSet = true;
}

qint32
SWGFreqTrackerSettings::getLog2Decim() {
    return log2_decim;
}
void
SWGFreqTrackerSettings::setLog2Decim(qint32 log2_decim) {
    this->log2_decim = log2_decim;
    this->m_log2_decim_isSet = true;
}

float
SWGFreqTrackerSettings::getSquelch() {
    return squelch;
}
void
SWGFreqTrackerSettings::setSquelch(float squelch) {
    this->squelch = squelch;
    this->m_squelch_isSet = true;
}

qint32
SWGFreqTrackerSettings::getRgbColor() {
    return rgb_color;
}
void
SWGFreqTrackerSettings::setRgbColor(qint32 rgb_color) {
    this->rgb_color = rgb_color;
    this->m_rgb_color_isSet = true;
}

QString*
SWGFreqTrackerSettings::getTitle() {
    return title;
}
void
SWGFreqTrackerSettings::setTitle(QString* title) {
    this->title = title;
    this->m_title_isSet = true;
}

qint32
SWGFreqTrackerSettings::getSpanLog2() {
    return span_log2;
}
void
SWGFreqTrackerSettings::setSpanLog2(qint32 span_log2) {
    this->span_log2 = span_log2;
    this->m_span_log2_isSet = true;
}

float
SWGFreqTrackerSettings::getAlphaEma() {
    return alpha_ema;
}
void
SWGFreqTrackerSettings::setAlphaEma(float alpha_ema) {
    this->alpha_ema = alpha_ema;
    this->m_alpha_ema_isSet = true;
}

qint32
SWGFreqTrackerSettings::getTracking() {
    return tracking;
}
void
SWGFreqTrackerSettings::setTracking(qint32 tracking) {
    this->tracking = tracking;
    this->m_tracking_isSet = true;
}

qint32
SWGFreqTrackerSettings::getTrackerType() {
    return tracker_type;
}
void
SWGFreqTrackerSettings::setTrackerType(qint32 tracker_type) {
    this->tracker_type = tracker_type;
    this->m_tracker_type_isSet = true;
}

qint32
SWGFreqTrackerSettings::getPllPskOrder() {
    return pll_psk_order;
}
void
SWGFreqTrackerSettings::setPllPskOrder(qint32 pll_psk_order) {
    this->pll_psk_order = pll_psk_order;
    this->m_pll_psk_order_isSet = true;
}

qint32
SWGFreqTrackerSettings::getRrc() {
    return rrc;
}
void
SWGFreqTrackerSettings::setRrc(qint32 rrc) {
    this->rrc = rrc;
    this->m_rrc_isSet = true;
}

qint32
SWGFreqTrackerSettings::getRrcRolloff() {
    return rrc_rolloff;
}
void
SWGFreqTrackerSettings::setRrcRolloff(qint32 rrc_rolloff) {
    this->rrc_rolloff = rrc_rolloff;
    this->m_rrc_rolloff_isSet = true;
}

qint32
SWGFreqTrackerSettings::getSquelchGate() {
    return squelch_gate;
}
void
SWGFreqTrackerSettings::setSquelchGate(qint32 squelch_gate) {
    this->squelch_gate = squelch_gate;
    this->m_squelch_gate_isSet = true;
}

qint32
SWGFreqTrackerSettings::getStreamIndex() {
    return stream_index;
}
void
SWGFreqTrackerSettings::setStreamIndex(qint32 stream_index) {
    this->stream_index = stream_index;
    this->m_stream_index_isSet = true;
}

qint32
SWGFreqTrackerSettings::getUseReverseApi() {
    return use_reverse_api;
}
void
SWGFreqTrackerSettings::setUseReverseApi(qint32 use_reverse_api) {
    this->use_reverse_api = use_reverse_api;
    this->m_use_reverse_api_isSet = true;
}

QString*
SWGFreqTrackerSettings::getReverseApiAddress() {
    return reverse_api_address;
}
void
SWGFreqTrackerSettings::setReverseApiAddress(QString* reverse_api_address) {
    this->reverse_api_address = reverse_api_address;
    this->m_reverse_api_address_isSet = true;
}

qint32
SWGFreqTrackerSettings::getReverseApiPort() {
    return reverse_api_port;
}
void
SWGFreqTrackerSettings::setReverseApiPort(qint32 reverse_api_port) {
    this->reverse_api_port = reverse_api_port;
    this->m_reverse_api_port_isSet = true;
}

qint32
SWGFreqTrackerSettings::getReverseApiDeviceIndex() {
    return reverse_api_device_index;
}
void
SWGFreqTrackerSettings::setReverseApiDeviceIndex(qint32 reverse_api_device_index) {
    this->reverse_api_device_index = reverse_api_device_index;
    this->m_reverse_api_device_index_isSet = true;
}

qint32
SWGFreqTrackerSettings::getReverseApiChannelIndex() {
    return reverse_api_channel_index;
}
void
SWGFreqTrackerSettings::setReverseApiChannelIndex(qint32 reverse_api_channel_index) {
    this->reverse_api_channel_index = reverse_api_channel_index;
    this->m_reverse_api_channel_index_isSet = true;
}

SWGGLSpectrum*
SWGFreqTrackerSettings::getSpectrumConfig() {
    return spectrum_config;
}
void
SWGFreqTrackerSettings::setSpectrumConfig(SWGGLSpectrum* spectrum_config) {
    this->spectrum_config = spectrum_config;
    this->m_spectrum_config_isSet = true;
}

SWGChannelMarker*
SWGFreqTrackerSettings::getChannelMarker() {
    return channel_marker;
}
void
SWGFreqTrackerSettings::setChannelMarker(SWGChannelMarker* channel_marker) {
    this->channel_marker = channel_marker;
    this->m_channel_marker_isSet = true;
}

SWGRollupState*
SWGFreqTrackerSettings::getRollupState() {
    return rollup_state;
}
void
SWGFreqTrackerSettings::setRollupState(SWGRollupState* rollup_state) {
    this->rollup_state = rollup_state;
    this->m_rollup_state_isSet = true;
}


bool
SWGFreqTrackerSettings::isSet(){
    bool isObjectUpdated = false;
    do{
        if(m_input_frequency_offset_isSet){
            isObjectUpdated = true; break;
        }
        if(m_rf_bandwidth_isSet){
            isObjectUpdated = true; break;
        }
        if(m_log2_decim_isSet){
            isObjectUpdated = true; break;
        }
        if(m_squelch_isSet){
            isObjectUpdated = true; break;
        }
        if(m_rgb_color_isSet){
            isObjectUpdated = true; break;
        }
        if(title && *title != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_span_log2_isSet){
            isObjectUpdated = true; break;
        }
        if(m_alpha_ema_isSet){
            isObjectUpdated = true; break;
        }
        if(m_tracking_isSet){
            isObjectUpdated = true; break;
        }
        if(m_tracker_type_isSet){
            isObjectUpdated = true; break;
        }
        if(m_pll_psk_order_isSet){
            isObjectUpdated = true; break;
        }
        if(m_rrc_isSet){
            isObjectUpdated = true; break;
        }
        if(m_rrc_rolloff_isSet){
            isObjectUpdated = true; break;
        }
        if(m_squelch_gate_isSet){
            isObjectUpdated = true; break;
        }
        if(m_stream_index_isSet){
            isObjectUpdated = true; break;
        }
        if(m_use_reverse_api_isSet){
            isObjectUpdated = true; break;
        }
        if(reverse_api_address && *reverse_api_address != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_reverse_api_port_isSet){
            isObjectUpdated = true; break;
        }
        if(m_reverse_api_device_index_isSet){
            isObjectUpdated = true; break;
        }
        if(m_reverse_api_channel_index_isSet){
            isObjectUpdated = true; break;
        }
        if(spectrum_config && spectrum_config->isSet()){
            isObjectUpdated = true; break;
        }
        if(channel_marker && channel_marker->isSet()){
            isObjectUpdated = true; break;
        }
        if(rollup_state && rollup_state->isSet()){
            isObjectUpdated = true; break;
        }
    }while(false);
    return isObjectUpdated;
}
}

