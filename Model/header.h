#ifndef MODEL_HEADER_H
#define MODEL_HEADER_H
#include "Global/lib.h"
#include "Transform/lib.h"
#include "DataStruct/lib.h"
#include "Drawing/lib.h"
#include "Matrix/lib.h"

namespace NModel
{
    enum MODEL_TYPE
    {
        MODEL_PART,
        MODEL_MOVABLEPART,
        MODEL_APP_ARRAYPART,
    };
}

#endif // HEADER_H
