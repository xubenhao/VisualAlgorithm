//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef PARAMETER_ARRAYNCPARAMETER_H
#define PARAMETER_ARRAYNCPARAMETER_H

#include "ncparameter.h"
namespace NParameter
{

    class ArrayNcElement
    {
    public:
        ArrayNcElement()
        {
            m_nDefault = COLOR_1;
            m_nNotMatch = COLOR_2;
            m_nMatch = COLOR_3;
            memset(m_strContent, 0, sizeof(m_strContent));
            memset(m_strName, 0, sizeof(m_strName));
            m_nObjectId = -1;
        }

        Size m_nSize;
        COLOR m_nDefault;
        COLOR m_nNotMatch;
        COLOR m_nMatch;
        char m_strContent[100];
        char m_strName[100];
        long m_nObjectId;
    };

    class ArrayNcParameter : public NcParameter
    {
    public:
        ArrayNcParameter()
        {
            m_nSize = 0;
            m_nCapacity = 0;
            m_nDefToFirstLen = 100.0;
            m_nDefToFirstAngle = 0.0;
            memset(m_strScaleName, 0, sizeof(m_strScaleName));
            m_nScaleId = -1;
        }

    public:
        int m_nSize;
        int m_nCapacity;
        NDataStruct::DynArray<ArrayNcElement> m_arrElements;
        char m_strScaleName[100];
        long m_nScaleId;
        double m_nDefToFirstLen;
        double m_nDefToFirstAngle;
    };
}

#endif // ARRAYNCPARAMETER_H
