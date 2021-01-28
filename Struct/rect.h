//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef STRUCT_RECT_H
#define STRUCT_RECT_H
#include "header.h"
#include "point.h"

namespace NTransform
{
    class MatrixTransform;
}

namespace NStruct
{
    class Rect
    {
    public:
        Rect();

        Point GetLeftUp() const {return m_poLeftUp;}
        void SetLeftUp(const Point& poP_){m_poLeftUp = poP_;}
        double GetWeight() const {return m_nWeight;}
        void SetWeight(double nWeight_){m_nWeight = nWeight_;}
        double GetHeight() const {return m_nHeight;}
        void SetHeight(double nHeight_){m_nHeight = nHeight_;}
        double GetCalcAngle() const {return m_nCalcAngle;}
        void SetCalcAngle(double nCalcAngle_){m_nCalcAngle = nCalcAngle_;}

        Point GetRightBottom() const;
        Polyline ToPolyLine() const ;
        QRectF ToQRectF() const;
    private:
        Point m_poLeftUp;
        double m_nWeight;
        double m_nHeight;
        double m_nCalcAngle;

        friend NTransform::MatrixTransform;
    };
}

#endif // RECT_H
