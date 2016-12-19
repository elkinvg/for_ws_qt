#ifndef COMMON_WS_H
#define COMMON_WS_H

#include <QString>
//#include <string>
#include <vector>
//using std::string;
using std::vector;

enum CmdArgType_FromTango {
    DEV_VOID = 0,
    DEV_BOOLEAN,
    DEV_SHORT,
    DEV_LONG,
    DEV_FLOAT,
    DEV_DOUBLE,
    DEV_USHORT,
    DEV_ULONG,
    DEV_STRING,
    DEVVAR_CHARARRAY,
    DEVVAR_SHORTARRAY,
    DEVVAR_LONGARRAY,
    DEVVAR_FLOATARRAY,
    DEVVAR_DOUBLEARRAY,
    DEVVAR_USHORTARRAY,
    DEVVAR_ULONGARRAY,
    DEVVAR_STRINGARRAY,
    DEVVAR_LONGSTRINGARRAY,
    DEVVAR_DOUBLESTRINGARRAY,
    DEV_STATE,
    CONST_DEV_STRING,
    DEVVAR_BOOLEANARRAY,
    DEV_UCHAR,
    DEV_LONG64,
    DEV_ULONG64,
    DEVVAR_LONG64ARRAY,
    DEVVAR_ULONG64ARRAY,
    DEV_INT,
    DEV_ENCODED,
    DEV_ENUM,
    DEV_PIPE_BLOB,
    DEVVAR_STATEARRAY,
    DATA_TYPE_UNKNOWN = 100
};

enum AttrDataFormat_FromTango { SCALAR, SPECTRUM, IMAGE, FMT_UNKNOWN};

enum class TypeReq {ATTRIBUTE,COMMAND,UNKNOWN};
enum class ValOrArr {VALUE,ARRAY,UNKNOWN};
enum class TypeData {BOOL,INT,DOUBLE,STRING,NONE};

struct TangoAttrSpectrOrImage
{
    bool hasData {false};
    TypeData typeData {TypeData::NONE};

    int dimX {0};
    int dimY {0};

    vector<QString> ansStringArray;
    vector<bool> ansBoolArray;
    vector<int> ansIntArray;
    vector<double> ansDoubleArray;
};

struct TangoAttrOrCommandVal
{
    bool hasData {false};
    TypeData typeData {TypeData::NONE};

    QString strVal;
    bool boolVal;
    int intVal;
    double doubleVal;
};


struct TangoCommAnsArr
{
    bool hasData {false};
    TypeData typeData {TypeData::NONE};

    vector<QString> ansStringArray;
    vector<bool> ansBoolArray;
    vector<int> ansIntArray;
    vector<double> ansDoubleArray;
};

struct TangoDataFromCommand
{
    ValOrArr varOrArr {ValOrArr::UNKNOWN};
    QString commandName;
    QString idReq;
    TangoCommAnsArr argoutArray;
    TangoAttrOrCommandVal argoutValue;
};

struct TangoDataFromAttribute {
    ValOrArr varOrArr {ValOrArr::UNKNOWN};
    QString attrName;
    QString qual;
    int timestamp;
    TangoAttrOrCommandVal retValue;
    TangoAttrSpectrOrImage retArray;
};

struct ErrorData
{
    QString errorMess;
    QString command_name;
    QString id_req;
};

struct ParsedWsJsonData
{
    // тип запроса для возвращаемых данных
    TypeReq typeReq {TypeReq::UNKNOWN};
    // Является ли сообщением об ошибке
    bool hasError {false};
    // Данные об ошибках из сервера, сейчас в-основном размер равен 1, в случае
    // наличия сообщений об ошибках
    vector<ErrorData> errorData;
    // Возвращаемые данные для атрибутов
    vector<TangoDataFromAttribute> dataFromAttr;
    // Возвращаемые данные для команд
    TangoDataFromCommand dataFromCommand;
};

#endif // COMMON_WS_H
