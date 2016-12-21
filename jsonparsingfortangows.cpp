#include "jsonparsingfortangows.h"

#include "common_ws.h"

#include <QJsonDocument>


ParsedWsJsonData JsonParsingForTangoWs::parseJson(const QString &json, bool onlyCommand)
{
    QJsonDocument jsondoc = QJsonDocument::fromJson(json.toUtf8());
    ParsedWsJsonData parsedJsonData;

    if (jsondoc.isNull())
        return parsedJsonData;

    if(jsondoc.isObject()) {

        QJsonObject jsonObj = jsondoc.object();
        TypeReq typeReq;
        auto isEvent = jsonObj.contains("event");
        if (!isEvent)
            return parsedJsonData;
        bool hasData = jsonObj.contains("data");

        if (jsonObj["event"].toString() == "read") {
            if(jsonObj.find("type_req") != jsonObj.end()) {
                if(jsonObj["type_req"] == "attribute") {
                    parsedJsonData.typeReq = TypeReq::ATTRIBUTE;
                    if (onlyCommand)
                        return parsedJsonData;

                    if (hasData) {
                        if (jsonObj["data"].isArray()) {
                            QJsonArray dataArr = jsonObj["data"].toArray();
                            parsedJsonData.dataFromAttr = getDataFromAttr(dataArr);
                        }
                    }
                }
                if(jsonObj["type_req"] == "command") {
                    parsedJsonData.typeReq = TypeReq::COMMAND;
                    if (hasData) {
                        if (jsonObj["data"].isObject()) {
                            QJsonObject dataComm = jsonObj["data"].toObject();
                            parsedJsonData.dataFromCommand = getDataFromComm(dataComm);
                        }
                    }
                }
            }
        }
        if (jsonObj["event"].toString() == "error") {
            parsedJsonData.hasError = true;
            vector<ErrorData> vecErr;
            ErrorData errDt;
            if (hasData) {
                if (jsonObj["data"].isArray()) {
                    QJsonArray errorArray = jsonObj["data"].toArray();
                    if (errorArray[0].isObject()) {
                        QJsonObject fromErr = errorArray[0].toObject();
                        if (!fromErr.contains("type_req")) {
                            return parsedJsonData;
                        }
                        if(fromErr["type_req"].toString() == "attribute")
                            parsedJsonData.typeReq = TypeReq::ATTRIBUTE;
                        if(fromErr["type_req"].toString() == "command")
                            parsedJsonData.typeReq = TypeReq::COMMAND;

                        if (fromErr.contains("error")) {
                            errDt.errorMess = fromErr["error"].toString();
                        }
                        if (fromErr.contains("id_req")) {
                            if (fromErr["id_req"].isString())
                                errDt.id_req = fromErr["id_req"].toString();
                            if (fromErr["id_req"].isDouble())
                                errDt.id_req = QString::number(fromErr["id_req"].toDouble());
                        }
                        if (fromErr.contains("command_name")) {
                            errDt.command_name = fromErr["command_name"].toString();
                        }
                        vecErr.push_back(errDt);
                        parsedJsonData.errorData = vecErr;
                    }
                }
            }
        }
    }

    return parsedJsonData;
}

QString JsonParsingForTangoWs::generateJsonForCommand(QString command)
{
    QJsonDocument json;
    QJsonObject jObj;
    jObj.insert("command",command);
    json.setObject(jObj);
    return json.toJson(QJsonDocument::Compact);
}

QString JsonParsingForTangoWs::generateJsonForCommand(QString command, double val)
{
    QJsonDocument json;
    QJsonObject jObj;
    jObj.insert("command",command);
    jObj.insert("argin",val);
    json.setObject(jObj);
    return json.toJson(QJsonDocument::Compact);
}

QString JsonParsingForTangoWs::generateJsonForCommand(QString command, QString device, double val)
{
    QJsonDocument json;
    QJsonObject jObj;
    QJsonArray jArr = {device,QString::number(val)};
    jObj.insert("command",command);
    jObj.insert("argin",jArr);
    json.setObject(jObj);
    return json.toJson(QJsonDocument::Compact);
}

QString JsonParsingForTangoWs::generateJsonForCommand(QString command, QString device)
{
    QJsonDocument json;
    QJsonObject jObj;
    jObj.insert("command",command);
    jObj.insert("argin",device);
    json.setObject(jObj);
    return json.toJson(QJsonDocument::Compact);
}

vector<TangoDataFromAttribute> JsonParsingForTangoWs::getDataFromAttr(QJsonArray &data)
{
    vector<TangoDataFromAttribute> dataAttr;

    if (data.size() == 0)
        return dataAttr;

    for (const auto& ind: data) {
        if (!ind.isObject())
            continue;
        TangoDataFromAttribute tmp = getAttr(ind.toObject());
        dataAttr.push_back(tmp);
    }

    return dataAttr;
}

TangoDataFromCommand JsonParsingForTangoWs::getDataFromComm(QJsonObject &comObj)
{
    TangoDataFromCommand dataComm;
    if (!comObj.contains("command_name") || !comObj.contains("argout") )
        return dataComm;

    if (!comObj["command_name"].isString() )
        return dataComm;

    dataComm.commandName = comObj["command_name"].toString();

    if (comObj.contains("id_req")) {
        if (comObj["id_req"].isString())
            dataComm.idReq = comObj["id_req"].toString();
        if (comObj["id_req"].isDouble())
            dataComm.idReq = QString::number(comObj["id_req"].toDouble());
    }

    if(comObj["argout"].isArray()) {
        dataComm.varOrArr = ValOrArr::ARRAY;
        dataComm.argoutArray = getCommArrayAns(comObj["argout"].toArray());
    }
    else if (comObj["argout"].isBool() || comObj["argout"].isDouble() || comObj["argout"].isString() ) {
        dataComm.varOrArr = ValOrArr::VALUE;
        QJsonValue jsVal = comObj["argout"];
        dataComm.argoutValue = getAttrOrCommValue(jsVal);
    }

    return dataComm;
}

TangoCommAnsArr JsonParsingForTangoWs::getCommArrayAns(const QJsonArray &jsonArray)
{
    TangoCommAnsArr outComm;
    if (jsonArray.size()>0) {
        if (jsonArray[0].isBool()) {
            outComm.typeData = TypeData::BOOL;
            outComm.ansBoolArray = dataFromJsonArrayBool(jsonArray);
            outComm.hasData = true;
        }
        if (jsonArray[0].isDouble()) {
            outComm.typeData = TypeData::DOUBLE;
            outComm.ansDoubleArray = dataFromJsonArrayDouble(jsonArray);
            outComm.hasData = true;
        }
        if (jsonArray[0].isString()) {
            outComm.typeData = TypeData::STRING;
            outComm.ansStringArray = dataFromJsonArrayString(jsonArray);
            outComm.hasData = true;
        }
    }

    return outComm;
}

TangoDataFromAttribute JsonParsingForTangoWs::getAttr(const QJsonObject& attrObj)
{
    TangoDataFromAttribute attrDt;

    if (!attrObj.contains("attr") || !attrObj.contains("data") )
        return attrDt;

    if (!attrObj["attr"].isString())
        return attrDt;

    attrDt.attrName = attrObj["attr"].toString();


    if (attrObj.contains("qual")) {
        if (attrObj["qual"].isString())
           attrDt.qual = attrObj["qual"].toString();
    }

    if (attrObj.contains("time")) {
        if (attrObj["time"].isDouble())
           attrDt.timestamp = attrObj["time"].toInt();
    }

    if(attrObj["data"].isArray()) {
        attrDt.varOrArr = ValOrArr::ARRAY;
        QJsonArray arr = attrObj["data"].toArray();
        TangoAttrSpectrOrImage spectrOrImage = getAttrSpectrOrImage(arr);

        if (attrObj.contains("dimX"))
                spectrOrImage.dimX = attrObj["dimX"].toInt();
        if (attrObj.contains("dimY"))
                spectrOrImage.dimY = attrObj["dimY"].toInt();

        attrDt.retArray = spectrOrImage;
    }
    else if (attrObj["data"].isBool() || attrObj["data"].isDouble() || attrObj["data"].isString() ) {
        attrDt.varOrArr = ValOrArr::VALUE;
        QJsonValue jsVal = attrObj["data"];
        attrDt.retValue = getAttrOrCommValue(jsVal);
    }

    return attrDt;
}

TangoAttrSpectrOrImage JsonParsingForTangoWs::getAttrSpectrOrImage(QJsonArray &jsonArray)
{
    TangoAttrSpectrOrImage spectrOrImage;

    if (jsonArray.size()>0) {
        if (jsonArray[0].isBool()) {
            spectrOrImage.typeData = TypeData::BOOL;
            spectrOrImage.ansBoolArray = dataFromJsonArrayBool(jsonArray);
            spectrOrImage.hasData = true;
        }
        if (jsonArray[0].isDouble()) {
            spectrOrImage.typeData = TypeData::DOUBLE;
            spectrOrImage.ansDoubleArray = dataFromJsonArrayDouble(jsonArray);
            spectrOrImage.hasData = true;
        }
        if (jsonArray[0].isString()) {
            spectrOrImage.typeData = TypeData::STRING;
            spectrOrImage.ansStringArray = dataFromJsonArrayString(jsonArray);
            spectrOrImage.hasData = true;
        }
    }

    return spectrOrImage;
}

TangoAttrOrCommandVal JsonParsingForTangoWs::getAttrOrCommValue(QJsonValue &jsonVal)
{
    TangoAttrOrCommandVal out;

    if (jsonVal.isBool()) {
        out.boolVal = jsonVal.toBool();
        out.typeData = TypeData::BOOL;
        out.hasData = true;
    }
    if (jsonVal.isDouble()) {
        out.doubleVal = jsonVal.toDouble();
        out.typeData = TypeData::DOUBLE;
        out.hasData = true;
    }
    if (jsonVal.isString()) {
        out.strVal = jsonVal.toString();
        out.typeData = TypeData::STRING;
        out.hasData = true;
    }

    return out;
}

vector<double> JsonParsingForTangoWs::dataFromJsonArrayDouble(const QJsonArray &arr)
{
    vector<double> out;
    for (const auto& iter: arr) {
        out.push_back(iter.toDouble());
    }
    return out;
}

vector<QString> JsonParsingForTangoWs::dataFromJsonArrayString(const QJsonArray &arr)
{
    vector<QString> out;
    for (const auto& iter: arr) {
        out.push_back(iter.toString());
    }
    return out;
}

vector<bool> JsonParsingForTangoWs::dataFromJsonArrayBool(const QJsonArray &arr)
{
    vector<bool> out;
    for (const auto& iter: arr) {
        out.push_back(iter.toBool());
    }
    return out;
}


