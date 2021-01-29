#ifndef TRANSFORM_HEADER_H
#define TRANSFORM_HEADER_H
#include "Global/lib.h"
#include "Matrix/lib.h"
#include "Vector/lib.h"
#include "DataStruct/lib.h"
#include "Struct/lib.h"

namespace NTransform
{
    enum TRANSFORM_TYPE
    {
        TRANSFORM_TRANSFORM,
        TRANSFORM_LINEAR,
        TRANSFORM_ROTATE,
        TRANSFORM_SCALE,
        TRANSFORM_MATRIX,
        TRANSFORM_GROUP,
    };
}

#endif // HEADER_H
