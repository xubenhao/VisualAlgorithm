//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#include "point.h"

namespace NStruct
{
    Point operator-(const Point& poOne_, const Point& poTwo_)
    {
        Point _poRet;
        _poRet.m_nX = poOne_.m_nX - poTwo_.m_nX;
        _poRet.m_nY = poOne_.m_nY - poTwo_.m_nY;
        return _poRet;
    }

    Point operator+(const Point& poOne_, const Point& poTwo_)
    {
        Point _poRet;
        _poRet.m_nX = poOne_.m_nX + poTwo_.m_nX;
        _poRet.m_nY = poOne_.m_nY + poTwo_.m_nY;
        return _poRet;
    }

    Point operator/(const Point& poP_, double nDivide_)
    {
        Point _poRet;
        _poRet.m_nX = poP_.m_nX / nDivide_;
        _poRet.m_nY = poP_.m_nY / nDivide_;
        return _poRet;
    }

    double Distance(const Point& poOne_, const Point& poTwo_)
    {
        double _nX = poOne_.m_nX - poTwo_.m_nX;
        double _nY = poOne_.m_nY - poTwo_.m_nY;
        return sqrt(_nX * _nX + _nY * _nY);
    }

    Point::Point()
    {
        m_nX = 0.0;
        m_nY = 0.0;
    }

    Point::Point(double nX_, double nY_)
    {
        m_nX = nX_;
        m_nY = nY_;
    }

    QPointF Point::toQPointF()
    {
        return QPointF(m_nX, m_nY);
    }
}

