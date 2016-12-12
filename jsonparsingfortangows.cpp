#include "jsonparsingfortangows.h"

#include "common_ws.h"

#include <QJsonDocument>

#include <iostream>
using std::cout;
using std::endl;

JsonParsingForTangoWs::JsonParsingForTangoWs()
{

}

TangoDataFromJson* JsonParsingForTangoWs::parseJson(const QString &json)
{
    QJsonDocument jsondoc = QJsonDocument::fromJson(json.toUtf8());

    if (jsondoc.isNull())
        return nullptr;

    if(jsondoc.isObject()) {
        cout << "jsondoc.isObject()" << endl;
        QJsonObject jsonObj = jsondoc.object();
        TypeReq typeReq;
        auto isEvent = jsonObj.contains("event");
        bool hasData = jsonObj.contains("data");

        if(jsonObj.find("type_req") != jsonObj.end()) {
            if(jsonObj["type_req"] == "attribute") {
                typeReq = TypeReq::ATTRIBUTE;
                if (hasData) {
                    QJsonValue data = jsonObj["data"];
                    auto isa = data.isArray();
                    if (data.isArray()) {
                        getFromAttrData(data.toArray());
                    }
                    //QJsonObject dataObj = data.toObject();

                }
            }
            if(jsonObj["type_req"] == "command") {
                typeReq = TypeReq::COMMAND;
                cout << "-------------COMMAND-------------" << endl;
            }
        }
    }

    return nullptr;
}

void JsonParsingForTangoWs::getFromAttrData(QJsonArray &attrDataJson)
{
    int size = attrDataJson.size();
    QJsonObject out = attrDataJson[0].toObject();

}

void JsonParsingForTangoWs::getFromCommandData(QJsonObject &commDataJson)
{

}
