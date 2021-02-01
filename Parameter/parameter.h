//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef PARAMETER_PARAMETER_H
#define PARAMETER_PARAMETER_H
#include "header.h"

namespace NParameter
{
    #define COLOR_0 COLOR(255, 255, 255, 255)
    #define COLOR_1 COLOR(255, 255, 204, 255)
    #define COLOR_2 COLOR(204, 255, 255, 255)
    #define COLOR_3 COLOR(255, 204, 204, 255)
    #define COLOR_4 COLOR(204, 204, 255, 255)

    #define COLOR_5 COLOR(255, 153, 102, 255)
    #define COLOR_6 COLOR(255, 102, 102, 255)
    #define COLOR_7 COLOR(204, 255, 153, 255)
    #define COLOR_8 COLOR(204, 255, 204, 255)
    #define COLOR_9 COLOR(153, 204, 153, 255)
    #define COLOR_10 COLOR(153, 153, 153, 255)
    #define COLOR_11 COLOR(255, 255, 255, 255)

    //0 QColor(255, 255, 255),
    //1 QColor(255, 255, 204),
    //2 QColor(204, 255, 255),
    //3 QColor(255, 204, 204),
    //4 QColor(204, 204, 255),
    //5 QColor(255, 153, 102),
    //6 QColor(255, 102, 102),
    //7 QColor(204, 255, 153),
    //8 QColor(204, 255, 204),
    //9 QColor(153, 204, 153),

    class Size
    {
    public:
        Size()
        {
            m_nHeight = 20.0;
            m_nWidth = 80.0;
        }

        double m_nWidth;
        double m_nHeight;
    };

    struct Pen
    {
    public:
        Pen()
        {
           m_nColor = COLOR_0;
           m_nWidth = 2.0;
        }

        COLOR m_nColor;
        double m_nWidth;
    };

    class Brush
    {
    public:
        Brush()
        {
            m_nColor = COLOR_0;
        }

        COLOR m_nColor;
    };

    class Font
    {
    public:
        Font()
        {
            strncpy(m_strFamily, "Times", 100);
            m_nPointSize = 40;
            m_nWeight = QFont::Bold;
            m_bItalic = false;
        }

        char m_strFamily[100];
        int m_nPointSize;
        int m_nWeight;
        bool m_bItalic;
    };


    QPen GetPen(COLOR nColor_, double nWidth_);
    QBrush GetBrush(COLOR nColor_);
    QColor GetColor(COLOR nColor_);
    int ColorToInt(COLOR nColor_);
    COLOR IntToColor(int nIndex_);
    class Parameter
    {
    public:
        Parameter();
    };
}


#endif // PARAMETER_H
