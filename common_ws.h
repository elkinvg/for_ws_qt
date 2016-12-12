#ifndef COMMON_WS_H
#define COMMON_WS_H

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

enum class TypeReq {ATTRIBUTE,COMMAND};
enum class ValOrArr {VALUE,ARRAY};
enum class TypeData {BOOL,INT,DOUBLE,STRING,NONE};

struct tangoAttrSpectrOrImage
{
    bool hasData {false};
    TypeData typeData {TypeData::NONE};

    int dimX;
    int dimY;

    vector<string> ansStringArray;
    vector<bool> ansBoolArray;
    vector<int> ansIntArray;
    vector<double> ansDoubleArray;
};

struct tangoAttrOrCommandVal
{
    bool hasData {false};
    TypeData typeData {TypeData::NONE};

    string strVal;
    bool boolVal;
    int intVal;
    double doubleVal;
};


struct tangoCommAnsArr
{
    bool hasData {false};
    TypeData typeData {TypeData::NONE};

    vector<string> ansStringArray;
    vector<bool> ansBoolArray;
    vector<int> ansIntArray;
    vector<double> ansDoubleArray;
};

struct parsedWsJsonData
{
    TypeReq typeReq;
    TypeData typeData;
    string nameCommOrAttr;
    string idReq;

    vector<string> ansStringArray;
    vector<bool> ansBoolArray;
    vector<int> ansIntArray;
    vector<double> ansDoubleArray;

    tangoAttrSpectrOrImage attrArray;

    string ansString;
    bool ansBool;
};

#endif // COMMON_WS_H
