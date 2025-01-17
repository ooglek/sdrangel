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


#include "SWGRollupState.h"

#include "SWGHelpers.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

namespace SWGSDRangel {

SWGRollupState::SWGRollupState(QString* json) {
    init();
    this->fromJson(*json);
}

SWGRollupState::SWGRollupState() {
    version = 0;
    m_version_isSet = false;
    children_states = nullptr;
    m_children_states_isSet = false;
}

SWGRollupState::~SWGRollupState() {
    this->cleanup();
}

void
SWGRollupState::init() {
    version = 0;
    m_version_isSet = false;
    children_states = new QList<SWGRollupChildState*>();
    m_children_states_isSet = false;
}

void
SWGRollupState::cleanup() {

    if(children_states != nullptr) { 
        auto arr = children_states;
        for(auto o: *arr) { 
            delete o;
        }
        delete children_states;
    }
}

SWGRollupState*
SWGRollupState::fromJson(QString &json) {
    QByteArray array (json.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
    return this;
}

void
SWGRollupState::fromJsonObject(QJsonObject &pJson) {
    ::SWGSDRangel::setValue(&version, pJson["version"], "qint32", "");
    
    
    ::SWGSDRangel::setValue(&children_states, pJson["childrenStates"], "QList", "SWGRollupChildState");
}

QString
SWGRollupState::asJson ()
{
    QJsonObject* obj = this->asJsonObject();

    QJsonDocument doc(*obj);
    QByteArray bytes = doc.toJson();
    delete obj;
    return QString(bytes);
}

QJsonObject*
SWGRollupState::asJsonObject() {
    QJsonObject* obj = new QJsonObject();
    if(m_version_isSet){
        obj->insert("version", QJsonValue(version));
    }
    if(children_states && children_states->size() > 0){
        toJsonArray((QList<void*>*)children_states, obj, "childrenStates", "SWGRollupChildState");
    }

    return obj;
}

qint32
SWGRollupState::getVersion() {
    return version;
}
void
SWGRollupState::setVersion(qint32 version) {
    this->version = version;
    this->m_version_isSet = true;
}

QList<SWGRollupChildState*>*
SWGRollupState::getChildrenStates() {
    return children_states;
}
void
SWGRollupState::setChildrenStates(QList<SWGRollupChildState*>* children_states) {
    this->children_states = children_states;
    this->m_children_states_isSet = true;
}


bool
SWGRollupState::isSet(){
    bool isObjectUpdated = false;
    do{
        if(m_version_isSet){
            isObjectUpdated = true; break;
        }
        if(children_states && (children_states->size() > 0)){
            isObjectUpdated = true; break;
        }
    }while(false);
    return isObjectUpdated;
}
}

