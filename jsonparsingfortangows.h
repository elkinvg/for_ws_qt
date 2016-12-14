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
    static TangoDataFromAttribute getAttr(const QJsonObject &attrObj);

    static TangoAttrSpectrOrImage getAttrSpectrOrImage(QJsonArray& jsonArray);
    static TangoAttrOrCommandVal getAttrOrCommValue(QJsonValue& jsonVal);

    static vector<double> dataFromJsonArrayDouble(const QJsonArray &arr);
    static vector<string> dataFromJsonArrayString(const QJsonArray &arr);
    static vector<bool> dataFromJsonArrayBool(const QJsonArray &arr);


    static TangoDataFromCommand getDataFromComm(QJsonObject &comObj);
    static TangoCommAnsArr getCommArrayAns(const QJsonArray &jsonArray);
};

#endif // JSONPARSINGFORTANGOWS_H
