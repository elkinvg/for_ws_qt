#include "jsonparsingfortangows.h"

#include "common_ws.h"

#include <QJsonDocument>

#include <iostream>
using std::cout;
using std::endl;

//JsonParsingForTangoWs::JsonParsingForTangoWs()
//{

//}

ParsedWsJsonData JsonParsingForTangoWs::parseJson(const QString &json)
{
    QJsonDocument jsondoc = QJsonDocument::fromJson(json.toUtf8());
    ParsedWsJsonData parsedJsonData;

    if (jsondoc.isNull())
        return parsedJsonData;

    if(jsondoc.isObject()) {

        QJsonObject jsonObj = jsondoc.object();
        TypeReq typeReq;
        auto isEvent = jsonObj.contains("event");
        bool hasData = jsonObj.contains("data");

        if(jsonObj.find("type_req") != jsonObj.end()) {
            if(jsonObj["type_req"] == "attribute") {
                parsedJsonData.typeReq = TypeReq::ATTRIBUTE;

                if (hasData) {
                    if (jsonObj["data"].isArray()) {
                        QJsonArray dataArr = jsonObj["data"].toArray();
                        parsedJsonData.dataFromAttr = getDataFromAttr(dataArr);
                    }
                }
            }
            if(jsonObj["type_req"] == "command") {
                parsedJsonData.typeReq = TypeReq::COMMAND;
                cout << "-------------COMMAND-------------" << endl;
                if (hasData) {
                    if (jsonObj["data"].isObject()) {
                        QJsonObject dataComm = jsonObj["data"].toObject();
                        parsedJsonData.dataFromCommand = getDataFromComm(dataComm);
                    }
                }
            }
        }
    }

    return parsedJsonData;
}

vector<TangoDataFromAttribute> JsonParsingForTangoWs::getDataFromAttr(QJsonArray &data)
{
    vector<TangoDataFromAttribute> dataAttr;

    if (data.size() == 0)
        return dataAttr;

    for (auto& ind: data) {
        if (!ind.isObject())
            continue;
        dataAttr.push_back(getAttr(ind.toObject()));
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

    dataComm.commandName = comObj["command_name"].toString().toStdString();

    if (comObj.contains("id_req")) {
        if (comObj["id_req"].isString())
            dataComm.idReq = comObj["id_req"].toString().toStdString();
        if (comObj["id_req"].isDouble())
            dataComm.idReq = std::to_string(comObj["id_req"].toDouble());
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

TangoCommAnsArr JsonParsingForTangoWs::getCommArrayAns(QJsonArray &jsonArray)
{
    TangoCommAnsArr outComm;
    if (jsonArray.size()>0) {
        if (jsonArray[0].isBool()) {
            outComm.typeData = TypeData::BOOL;
            outComm.ansBoolArray = dataFromJsonArrayBool(jsonArray,outComm.typeData);
            outComm.hasData = true;
        }
        if (jsonArray[0].isDouble()) {
            outComm.typeData = TypeData::DOUBLE;
            outComm.ansDoubleArray = dataFromJsonArrayDouble(jsonArray,outComm.typeData);
            outComm.hasData = true;
        }
        if (jsonArray[0].isString()) {
            outComm.typeData = TypeData::STRING;
            outComm.ansStringArray = dataFromJsonArrayString(jsonArray,outComm.typeData);
            outComm.hasData = true;
        }
    }

    return outComm;
}

TangoDataFromAttribute JsonParsingForTangoWs::getAttr(QJsonObject& attrObj)
{
    TangoDataFromAttribute attrDt;

    if (!attrObj.contains("attr") || !attrObj.contains("data") )
        return attrDt;

    if (!attrObj["attr"].isString())
        return attrDt;

    attrDt.attrName = attrObj["attr"].toString().toStdString();


    if (attrObj.contains("qual")) {
        if (attrObj["qual"].isString())
           attrDt.qual = attrObj["qual"].toString().toStdString();
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
            spectrOrImage.ansBoolArray = dataFromJsonArrayBool(jsonArray,spectrOrImage.typeData);
            spectrOrImage.hasData = true;
        }
        if (jsonArray[0].isDouble()) {
            spectrOrImage.typeData = TypeData::DOUBLE;
            spectrOrImage.ansDoubleArray = dataFromJsonArrayDouble(jsonArray,spectrOrImage.typeData);
            spectrOrImage.hasData = true;
        }
        if (jsonArray[0].isString()) {
            spectrOrImage.typeData = TypeData::STRING;
            spectrOrImage.ansStringArray = dataFromJsonArrayString(jsonArray,spectrOrImage.typeData);
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
        out.strVal = jsonVal.toString().toStdString();
        out.typeData = TypeData::STRING;
        out.hasData = true;
    }

    return out;
}

vector<double> JsonParsingForTangoWs::dataFromJsonArrayDouble(QJsonArray &arr, TypeData td)
{
    vector<double> out;
    for (auto& iter: arr) {
        out.push_back(iter.toDouble());
    }
    return out;
}

vector<std::string> JsonParsingForTangoWs::dataFromJsonArrayString(QJsonArray &arr, TypeData td)
{
    vector<std::string> out;
    for (auto& iter: arr) {
        out.push_back(iter.toString().toStdString());
    }
    return out;
}

vector<bool> JsonParsingForTangoWs::dataFromJsonArrayBool(QJsonArray &arr, TypeData td)
{
    vector<bool> out;
    for (auto& iter: arr) {
        out.push_back(iter.toBool());
    }
    return out;
}


