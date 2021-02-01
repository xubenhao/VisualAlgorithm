#ifndef FILE_GENERATE_HEADER_H
#define FILE_GENERATE_HEADER_H
#include "Global/lib.h"
#include "DataStruct/lib.h"
#include "Struct/lib.h"
#include "Parameter/lib.h"
#include <QTextStream>

namespace NFileGenerate
{
    enum FILE_GEN_RET_CODE
    {
        SUCCESS = 0,
        FILE_NOT_EXIST,
        ACCESS_ERROR,
    };
}

#endif // HEADER_H
