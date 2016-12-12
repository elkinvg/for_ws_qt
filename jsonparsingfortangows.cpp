#include "jsonparsingfortangows.h"

#include "common_ws.h"
#include <QJsonObject>
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
        if(jsonObj.find("type_req")) {
            if(jsonObj["type_req"] == "attribute")
                typeReq = TypeReq::ATTRIBUTE;
            if(jsonObj["type_req"] == "command")
                typeReq = TypeReq::COMMAND;
        }
    }

    return nullptr;
}
