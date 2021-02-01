//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef PARAMETER_ARRAYMODELPARAMETER_H
#define PARAMETER_ARRAYMODELPARAMETER_H

#include "modelparameter.h"

namespace NParameter
{
    class Element
    {
    public:
        Element()
        {
            memset(m_nContent, 0, sizeof(m_nContent));
            memset(m_strName, 0, sizeof(m_strName));
            m_nObjectId = -1;
        }

        char m_nContent[100];
        Brush m_nBrush;
        Pen m_nPen;
        Font m_nFont;
        char m_strName[100];
        NModel::Position m_nPosition;
        long m_nObjectId;
    };

    class ElementAddress
    {
    public:
        ElementAddress()
        {
            m_nArrowLen1 = 10.0;
            m_nArrowLen2 = 30.0;
            memset(m_nContent, 0, sizeof(m_nContent));
            m_nFont.m_nPointSize = 10.0;
            m_nObjectId = -1;
        }

        double m_nArrowLen1;
        double m_nArrowLen2;
        Size m_nSize;
        char m_nContent[100];
        Pen m_nPen;
        Brush m_nBrush;
        Font m_nFont;
        long m_nObjectId;
    };

    class ElementIndex
    {
    public:
        ElementIndex()
        {
            m_nHorizontalLen = 5.0;
            m_nVerticalLen = 20.0;
            memset(m_nContent, 0, sizeof(m_nContent));
            m_nSize.m_nWidth = 60.0;
            m_nSize.m_nHeight = 30.0;
            m_nFont.m_nPointSize = 20.0;
            m_nObjectId = -1;
        }

        double m_nHorizontalLen;
        double m_nVerticalLen;
        Size m_nSize;
        char m_nContent[100];
        Pen m_nPen;
        Brush m_nBrush;
        Font m_nFont;
        long m_nObjectId;
    };

    class ArrayParameter : public ModelParameter
    {
    public:
        ArrayParameter()
        {
            m_nCapacity = 0;
            m_nSize = 0;
        }

        static ArrayParameter* GetGeneralParameter();
        static void GetPraticalParameter(
                int nCapacity_,
                ArrayParameter& nParam_);
        // Global Parameter
        int m_nCapacity;
        int m_nSize;
        NStruct::Point m_poStart;
        Pen m_nPen;
        Brush m_nBrush;
        Font m_nFont;
        Size m_nElementSize;
        NDataStruct::DynArray<Element> m_arrElements;
        NDataStruct::DynArray<ElementAddress> m_arrElementAddresses;
        NDataStruct::DynArray<ElementIndex> m_arrElementIndexes;
    private:
        static ArrayParameter* s_nArrayParam;
    };

}

#endif // ARRAYMODELPARAMETER_H
