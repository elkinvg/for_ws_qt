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
    static ParsedWsJsonData parseJson(const QString& json, bool onlyCommand = false);
    static QString generateJsonForCommand(QString command);
    static QString generateJsonForCommand(QString command, double val);
    static QString generateJsonForCommand(QString command, QString device, double val);
    static QString generateJsonForCommand(QString command, QString device);



private:

    static vector<TangoDataFromAttribute> getDataFromAttr(QJsonArray &data);
    static TangoDataFromAttribute getAttr(const QJsonObject &attrObj);

    static TangoAttrSpectrOrImage getAttrSpectrOrImage(QJsonArray& jsonArray);
    static TangoAttrOrCommandVal getAttrOrCommValue(QJsonValue& jsonVal);

    static vector<double> dataFromJsonArrayDouble(const QJsonArray &arr);
    static vector<QString> dataFromJsonArrayString(const QJsonArray &arr);
    static vector<bool> dataFromJsonArrayBool(const QJsonArray &arr);


    static TangoDataFromCommand getDataFromComm(QJsonObject &comObj);
    static TangoCommAnsArr getCommArrayAns(const QJsonArray &jsonArray);
};

#endif // JSONPARSINGFORTANGOWS_H
