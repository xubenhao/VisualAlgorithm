//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030 

#include "rect.h"
#include "polyline.h"

namespace NStruct
{
    Rect::Rect()
    {
        m_nWeight = 1.0;
        m_nHeight = 1.0;
        m_nCalcAngle = 0.0;;
    }

    Point Rect::GetRightBottom() const
    {
        Point _poRet;
        double _nLen = sqrt(m_nWeight * m_nWeight + m_nWeight * m_nWeight);
        double _nCalcAngle = m_nCalcAngle - PI * 0.25;
        _poRet.m_nX = m_poLeftUp.m_nX + _nLen * cos(_nCalcAngle);
        // at this
        // we normally set logic coordinate 
        // as x axis's left is x+,y axis's up is y+
        // but in screen coordinate,
        // x axis's left is x+,y axis's down is y+
        // we process at there,
        // but not certain whether this is the good place to do this.
        // --- 
        // the right place todo this
        // shoule be the point when all geometry have tranformed
        // at that point,we can add a tranform to solve
        // the logical and screen coordinate's difference
        // fix me
        _poRet.m_nY = m_poLeftUp.m_nY + (_nLen * sin(_nCalcAngle));
        return _poRet;
    }

    Polyline Rect::ToPolyLine() const
    {
        Polyline _nPolyline;
        Point _po1 = m_poLeftUp;
        Point _po2 = GetRightBottom();
        Point _po3 = Point(_po1.GetX(), _po2.GetY());
        Point _po4 = Point(_po2.GetX(), _po1.GetY());
        _nPolyline.Add(_po1);
        _nPolyline.Add(_po3);
        _nPolyline.Add(_po2);
        _nPolyline.Add(_po4);
        return _nPolyline;
    }

    QRectF Rect::ToQRectF() const
    {
        Point _po1 = m_poLeftUp;
        return QRectF(
            _po1.toQPointF(), 
            GetRightBottom().toQPointF());
    }
}

