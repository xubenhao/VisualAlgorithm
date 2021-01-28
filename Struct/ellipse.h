//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef STRUCT_ELLIPSE_H
#define STRUCT_ELLIPSE_H
#include "header.h"
#include "point.h"

namespace NTransform
{
    class MatrixTransform;
}

namespace NStruct
{
    class Ellipse
    {
    public:
        Ellipse();
        Point GetCenter(){return m_poCenter;}
        void SetCenter(const Point& poP_){m_poCenter = poP_;}
        double GetHRadius(){return m_nHRadius;}
        void SetHRadius(double nHRadius_){m_nHRadius = nHRadius_;}
        double GetVRadius(){return m_nVRadius;}
        void SetVRadius(double nVRadius_){m_nVRadius = nVRadius_;}
    private:
        Point m_poCenter;
        double m_nHRadius;
        double m_nVRadius;

        friend NTransform::MatrixTransform;
    };
}
#endif // ELLIPSE_H
