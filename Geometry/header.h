//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030
//
#ifndef GEOMETRY_HEADER_H
#define GEOMETRY_HEADER_H
#include "Global/lib.h"
#include "DataStruct/lib.h"
#include "Transform/lib.h"
#include "Struct/lib.h"

namespace NGeometry
{
    enum GEOMETRY_TYPE
    {
        GEOMETRY_GEOMETRY,
        GEOMETRY_POINT,
        GEOMETRY_LINE,
        GEOMETRY_RECT,
        GEOMETRY_ELLIPSE,
        GEOMETRY_POLYLINE,
        GEOMETRY_GROUP,
    };
}

#endif // HEADER_H
