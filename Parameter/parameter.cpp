//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "parameter.h"

namespace NParameter
{
    QColor GetColor(COLOR nColor_)
    {
        QColor _nColor(nColor_.m_nR, nColor_.m_nG, nColor_.m_nB, nColor_.m_nA);
        return _nColor;
    }

    COLOR IntToColor(int nIndex_)
    {
        NDataStruct::DynArray<COLOR> _arrColors;
        _arrColors.Add(COLOR_0);
        _arrColors.Add(COLOR_1);
        _arrColors.Add(COLOR_2);
        _arrColors.Add(COLOR_3);
        _arrColors.Add(COLOR_4);

        _arrColors.Add(COLOR_5);
        _arrColors.Add(COLOR_6);
        _arrColors.Add(COLOR_7);
        _arrColors.Add(COLOR_8);
        _arrColors.Add(COLOR_9);

        _arrColors.Add(COLOR_10);
        _arrColors.Add(COLOR_11);
        if(nIndex_ >= 0 && nIndex_ < _arrColors.GetSize())
        {
            return _arrColors[nIndex_];
        }
        else
        {
            return COLOR();
        }
    }

    int ColorToInt(COLOR nColor_)
    {
        NDataStruct::DynArray<COLOR> _arrColors;
        _arrColors.Add(COLOR_0);
        _arrColors.Add(COLOR_1);
        _arrColors.Add(COLOR_2);
        _arrColors.Add(COLOR_3);
        _arrColors.Add(COLOR_4);

        _arrColors.Add(COLOR_5);
        _arrColors.Add(COLOR_6);
        _arrColors.Add(COLOR_7);
        _arrColors.Add(COLOR_8);
        _arrColors.Add(COLOR_9);

        _arrColors.Add(COLOR_10);
        _arrColors.Add(COLOR_11);
        int _nIndex = _arrColors.Find([nColor_](const COLOR& nT_)->bool
        {
            if (nT_ == nColor_)
            {
                return true;
            }
            else
            {
                return false;
            }
        });
        if(_nIndex != -1)
        {
            return _nIndex;
        }
        else
        {
            assert(false);
            return 0;
        }
    }

    QPen GetPen(COLOR nColor_, double nWidth_)
    {
        QPen _nPen;
        _nPen.setColor(GetColor(nColor_));
        _nPen.setWidthF(nWidth_);
        return _nPen;
    }

    QBrush GetBrush(COLOR nColor_)
    {
        QBrush _nBrush;
        _nBrush.setColor(GetColor(nColor_));
        _nBrush.setStyle(Qt::BrushStyle::SolidPattern);
        return _nBrush;
    }

    Parameter::Parameter()
    {

    }
}

