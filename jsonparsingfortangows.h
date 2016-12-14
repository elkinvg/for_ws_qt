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
    //JsonParsingForTangoWs();
    static ParsedWsJsonData parseJson(const QString& json);

    static vector<TangoDataFromAttribute> getDataFromAttr(QJsonArray &data);
    static TangoDataFromAttribute getAttr(QJsonObject &attrObj);

    static TangoAttrSpectrOrImage getAttrSpectrOrImage(QJsonArray& jsonArray);
    static TangoAttrOrCommandVal getAttrOrCommValue(QJsonValue& jsonVal);

    static vector<double> dataFromJsonArrayDouble(QJsonArray &arr, TypeData td);
    static vector<string> dataFromJsonArrayString(QJsonArray &arr, TypeData td);
    static vector<bool> dataFromJsonArrayBool(QJsonArray &arr, TypeData td);


    static TangoDataFromCommand getDataFromComm(QJsonObject &comObj);
    static TangoCommAnsArr getCommArrayAns(QJsonArray& jsonArray);
};

#endif // JSONPARSINGFORTANGOWS_H
