#ifndef FILE_PARSE_HEADER_H
#define FILE_PARSE_HEADER_H
#include "Global/lib.h"
#include "DataStruct/lib.h"
#include "Model/lib.h"
#include "Parameter/lib.h"
#include "NcCode/lib.h"
namespace NFileParse
{
    enum FILE_PARSE_RET_CODE
    {
        SUCCESS = 0,
        EMPTY_FILE,
        FILE_NOT_EXIST,
        ACCESS_ERROR,
        FILE_FORMAT_ERR,
        FILE_FORMAT_ERR_FIRST_LINE_NOT_ARRAYMODEL,
        FILE_FORMAT_ERR_UNREAD_ARRAYMODEL_END,
        FILE_FORMAT_ERR_UNREAD_EXPECTED_ELEMENT,
        FILE_FORMAT_ERR_CAPACITY_FORMAT_ERR,
    };

    enum NCFILE_PARSE_RET_CODE
    {
        NC_SUCCESS = 0,
        NC_EMPTY_FILE,
        NC_FILE_NOT_EXIST,
        NC_UNEXPECTED_TAG,
        NC_UNEXPECTED_VALUE,
        NC_FILE_END,
    };
}
#endif // HEADER_H
