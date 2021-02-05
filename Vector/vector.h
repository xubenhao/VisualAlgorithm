//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H
#include "header.h"

namespace NVector
{
    class Vector2D
    {
    public:
        Vector2D();
        Vector2D(const NStruct::Point& po1_, const NStruct::Point& po2_);

        ~Vector2D();

        double GetLength() const;
        void Normalize();
        double GetAngle();
    public:
        double m_nX;
        double m_nY;
    };
}

#endif // VECTOR_H
