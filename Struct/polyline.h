//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef STRUCT_POLYLINE_H
#define STRUCT_POLYLINE_H
#include "header.h"
#include "point.h"

namespace NTransform
{
    class MatrixTransform;
}

namespace NStruct
{
    class Polyline
    {
    public:
        Polyline();
        void Add(const Point& nPoint_);
        Point Get(int nIndex_);
        int GetSize(){return m_arrPoints.GetSize();}

    private:
        NDataStruct::DynArray<Point> m_arrPoints;

        friend NTransform::MatrixTransform;
    };
}

#endif // POLYLINE_H
