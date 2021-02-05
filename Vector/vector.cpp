//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "vector.h"

namespace NVector
{
    Vector2D::Vector2D()
    {
        m_nX = 0.0;
        m_nY = 0.0;
    }

    Vector2D::Vector2D(
            const NStruct::Point& po1_, 
            const NStruct::Point& po2_)
    {
        m_nX = po2_.GetX() - po1_.GetX();
        m_nY = po2_.GetY() - po1_.GetY();
    }

    double Vector2D::GetLength() const
    {
        double _nLen = 0.0;
        _nLen += m_nX * m_nX;
        _nLen += m_nY * m_nY;
        return std::sqrt(_nLen);
    }

    void Vector2D::Normalize()
    {
        double _nLen = GetLength();
        if (_nLen == 0.0)
        {
            return;
        }

        m_nX /= _nLen;
        m_nY /= _nLen;
    }

    double Vector2D::GetAngle()
    {
        double _nLen = GetLength();
        if (_nLen == 0.0)
        {
            return 0.0;
        }

        Vector2D _nVec = *this;
        _nVec.Normalize();
        double _nCalcAngle = acos(_nVec.m_nX);
        if(abs(_nVec.m_nX) < 0.000001)
        {
            if(_nVec.m_nY > 0.0)
            {
                return PI / 2.0;
            }
            else
            {
                return 3.0 * PI / 2.0;
            }
        }
        else if(_nVec.m_nX > 0.0)
        {
            if(abs(_nVec.m_nY) < 0.000001)
            {
                return 0.0;
            }
            else if(_nVec.m_nY > 0.0)
            {
                return _nCalcAngle;
            }
            else
            {
                return -1.0 * _nCalcAngle;
            }
        }
        else
        {
            if(abs(_nVec.m_nY) < 0.000001)
            {
                return PI;
            }
            else if(_nVec.m_nY > 0.0)
            {
                return _nCalcAngle;
            }
            else
            {
                return 2.0 * PI - _nCalcAngle;
            }
        }
    }

    Vector2D::~Vector2D()
    {

    }
}
