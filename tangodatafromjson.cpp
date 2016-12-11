#include "tangodatafromjson.h"


TangoDataFromJson::TangoDataFromJson(const QString &jsonData)
{

}

int TangoDataFromJson::getTypeRequest()
{
    return type_request;
}

int TangoDataFromJson::getCmdArgType()
{
    return cmd_arg_type;
}

int TangoDataFromJson::getAttrDataFormat()
{
    return attr_data_format;
}

bool TangoDataFromJson::isValid()
{
    return _valid;
}
