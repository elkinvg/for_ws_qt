#ifndef JSONPARSINGFORTANGOWS_H
#define JSONPARSINGFORTANGOWS_H

#include <common_ws.h>

#include <QString>

#include <QJsonObject>
#include <QJsonArray>
//#include <QJsonValue>

class JsonParsingForTangoWs
{
public:
    JsonParsingForTangoWs();
    ParsedWsJsonData parseJson(const QString& json);

    vector<TangoDataFromAttribute> getDataFromAttr(QJsonArray &data);
    TangoDataFromAttribute getAttr(QJsonObject &attrObj);

    TangoAttrSpectrOrImage getAttrSpectrOrImage(QJsonArray& jsonArray);
    TangoAttrOrCommandVal getAttrValue(QJsonValue& jsonVal);

    vector<double> dataFromJsonArrayDouble(QJsonArray &arr, TypeData td);
    vector<string> dataFromJsonArrayString(QJsonArray &arr, TypeData td);
    vector<bool> dataFromJsonArrayBool(QJsonArray &arr, TypeData td);


    TangoDataFromCommand getDataFromComm(QJsonValue &data);

    void getFromCommandData(QJsonObject &commDataJson);
};

#endif // JSONPARSINGFORTANGOWS_H
