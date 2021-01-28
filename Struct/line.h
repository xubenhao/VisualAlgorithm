//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef STRUCT_LINE_H
#define STRUCT_LINE_H
#include "header.h"
#include "point.h"

namespace NTransform
{
    class MatrixTransform;
}

namespace NStruct
{
    class Line
    {
    public:
        Line();
        Line(const Point& poS_, const Point& poE_);

        Point GetStart(){return m_poStart;}
        void SetStart(const Point& poP_){m_poStart = poP_;}
        Point GetEnd(){return m_poEnd;}
        void SetEnd(const Point& poP_){m_poEnd = poP_;}
    private:
        Point m_poStart;
        Point m_poEnd;

        friend NTransform::MatrixTransform;
    };
}

#endif // LINE_H
