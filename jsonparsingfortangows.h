#ifndef JSONPARSINGFORTANGOWS_H
#define JSONPARSINGFORTANGOWS_H

#include <QString>
#include <tangodatafromjson.h>

class JsonParsingForTangoWs
{
public:
    JsonParsingForTangoWs();
    TangoDataFromJson *parseJson(const QString& json);
};

#endif // JSONPARSINGFORTANGOWS_H
