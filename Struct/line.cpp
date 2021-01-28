//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#include "line.h"

namespace NStruct
{
    Line::Line()
    {

    }

    Line::Line(const Point& poS_, const Point& poE_)
    {
        m_poStart = poS_;
        m_poEnd = poE_;
    }
}

