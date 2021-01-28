//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#ifndef STRUCT_POINT_H
#define STRUCT_POINT_H
#include "header.h"

namespace NTransform
{
    class Transform;
    class LinearTransform;
    class RotateTransform;
    class ScaleTransform;
    class MatrixTransform;
}

namespace NStruct
{
    class Rect;
    class Ellipse;
    class Polyline;
    class Line;
    class Point
    {
    public:
        Point();
        Point(double nX_, double nY_);
        double GetX() const {return m_nX;}
        void SetX(double nX_){m_nX = nX_;}
        double GetY() const {return m_nY;}
        void SetY(double nY_){m_nY = nY_;}
        QPointF toQPointF();
    private:
        double m_nX;
        double m_nY;

        friend Point operator-(const Point& poOne_, const Point& poTwo_);
        friend Point operator+(const Point& poOne_, const Point& poTwo_);
        friend Point operator/(const Point& poP_, double nDivide_);
        friend double Distance(const Point& poOne_, const Point& poTwo_);
        friend Rect;
        friend Ellipse;
        friend Polyline;
        friend Line;
        friend NTransform::Transform;
        friend NTransform::LinearTransform;
        friend NTransform::RotateTransform;
        friend NTransform::ScaleTransform;
        friend NTransform::MatrixTransform;
    };

    Point operator-(const Point& poOne_, const Point& poTwo_);
    Point operator+(const Point& poOne_, const Point& poTwo_);
    Point operator/(const Point& poP_, double nDivide_);
    double Distance(const Point& poOne_, const Point& poTwo_);
}

#endif // POINT_H
