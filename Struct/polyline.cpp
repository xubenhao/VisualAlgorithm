//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#include "polyline.h"

namespace NStruct
{
    Polyline::Polyline()
    {

    }

    void Polyline::Add(const Point& nPoint_)
    {
        m_arrPoints.Add(nPoint_);
    }

    Point Polyline::Get(int nIndex_)
    {
        int _nSize = m_arrPoints.GetSize();
        if(nIndex_ < 0 || nIndex_ >= _nSize)
        {
            return Point();
        }

        return m_arrPoints[nIndex_];
    }
}

