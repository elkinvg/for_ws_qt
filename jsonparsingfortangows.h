#ifndef JSONPARSINGFORTANGOWS_H
#define JSONPARSINGFORTANGOWS_H

#include <QString>
#include <tangodatafromjson.h>
#include <QJsonObject>
#include <QJsonArray>

class JsonParsingForTangoWs
{
public:
    JsonParsingForTangoWs();
    TangoDataFromJson *parseJson(const QString& json);
    void getFromAttrData(QJsonArray &attrDataJson);
    void getFromCommandData(QJsonObject &commDataJson);
};

#endif // JSONPARSINGFORTANGOWS_H
