#ifndef TANGODATAFROMJSON_H
#define TANGODATAFROMJSON_H

#include <QString>

class TangoDataFromJson
{
public:
    explicit TangoDataFromJson(const QString& jsonData);

    int getTypeRequest();
    int getCmdArgType();
    int getAttrDataFormat();
    bool isValid();
private:
    int type_request;
    int cmd_arg_type;
    int attr_data_format;
    bool _valid;
};

#endif // TANGODATAFROMJSON_H
