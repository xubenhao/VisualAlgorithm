//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arraymodelparameter.h"

namespace NParameter
{
    ArrayParameter* ArrayParameter::s_nArrayParam = nullptr;

    void ArrayParameter::GetPraticalParameter(
            int nCapacity_,
            ArrayParameter& nParam_)
    {
        ArrayParameter _nArrayParam;
        _nArrayParam.m_nCapacity = nCapacity_;
        _nArrayParam.m_nSize = 0;
        _nArrayParam.m_nPen.m_nColor = COLOR_9;
        _nArrayParam.m_nPen.m_nWidth = 10.0;
        _nArrayParam.m_nBrush.m_nColor = COLOR_11;
        _nArrayParam.m_nElementSize.m_nWidth = 80.0;
        _nArrayParam.m_nElementSize.m_nHeight = 80.0;

        for(int i = 0; i < nCapacity_; i++)
        {
            // Non-Valid Element
            //_nArrayParam.m_arrElements.Add(NParameter::Element());

            // ElementAddress
            NParameter::ElementAddress _nEleAddress;
            _nEleAddress.m_nPen.m_nColor = COLOR_9;
            _nEleAddress.m_nPen.m_nWidth = 4.0;

            char _strAddr[100];
            sprintf(_strAddr, "Addr+%d", i);
            strncpy(_nEleAddress.m_nContent, _strAddr, 100);
            _nArrayParam.m_arrElementAddresses.Add(_nEleAddress);

            // ElementIndex
            NParameter::ElementIndex _nEleIndex;
            _nEleIndex.m_nPen.m_nColor = COLOR_9;
            _nEleIndex.m_nPen.m_nWidth = 4.0;
            sprintf(_strAddr, "%d", i);
            strncpy(_nEleIndex.m_nContent, _strAddr, 100);
            _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
            _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
            _nArrayParam.m_arrElementIndexes.Add(_nEleIndex);
        }

        nParam_ = _nArrayParam;
    }


    ArrayParameter* ArrayParameter::GetGeneralParameter()
    {
        if(s_nArrayParam)
        {
            return s_nArrayParam;
        }

        ArrayParameter* _pArrayParam = new ArrayParameter();
        _pArrayParam->m_nCapacity = 7;
        _pArrayParam->m_nSize = 5;
        _pArrayParam->m_nPen.m_nColor = COLOR_9;
        _pArrayParam->m_nPen.m_nWidth = 10.0;
        _pArrayParam->m_nBrush.m_nColor = COLOR_11;
        _pArrayParam->m_nElementSize.m_nWidth = 80.0;
        _pArrayParam->m_nElementSize.m_nHeight = 80.0;

        // Element
        NParameter::Element _nEle;
        _nEle.m_nBrush.m_nColor = COLOR_2;
        _nEle.m_nPen.m_nColor = COLOR_9;
        _nEle.m_nPen.m_nWidth = 10.0;
        strncpy(_nEle.m_nContent, "1", 100);
        strncpy(_nEle.m_strName, "1", 100);
        _pArrayParam->m_arrElements.Add(_nEle);

        // ElementAddress
        NParameter::ElementAddress _nEleAddress;
        _nEleAddress.m_nPen.m_nColor = COLOR_9;
        _nEleAddress.m_nPen.m_nWidth = 4.0;

        strncpy(_nEleAddress.m_nContent, "Addr", 100);
        _pArrayParam->m_arrElementAddresses.Add(_nEleAddress);

        // ElementIndex
        NParameter::ElementIndex _nEleIndex;
        _nEleIndex.m_nPen.m_nColor = COLOR_9;
        _nEleIndex.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleIndex.m_nContent, "0", 100);
        _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
        _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
        _pArrayParam->m_arrElementIndexes.Add(_nEleIndex);

        // Element
        _nEle.m_nBrush.m_nColor = COLOR_3;
        _nEle.m_nPen.m_nColor = COLOR_9;
        _nEle.m_nPen.m_nWidth = 10.0;
        strncpy(_nEle.m_nContent, "2", 100);
        strncpy(_nEle.m_strName, "2", 100);
        _pArrayParam->m_arrElements.Add(_nEle);

        // ElementAddress
        _nEleAddress.m_nPen.m_nColor = COLOR_9;
        _nEleAddress.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleAddress.m_nContent, "Addr+1", 100);
        _pArrayParam->m_arrElementAddresses.Add(_nEleAddress);

        // ElementIndex
        _nEleIndex.m_nPen.m_nColor = COLOR_9;
        _nEleIndex.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleIndex.m_nContent, "1", 100);
        _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
        _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
        _pArrayParam->m_arrElementIndexes.Add(_nEleIndex);

        // Element
        _nEle.m_nBrush.m_nColor = COLOR_4;
        _nEle.m_nPen.m_nColor = COLOR_9;
        _nEle.m_nPen.m_nWidth = 10.0;
        strncpy(_nEle.m_nContent, "3", 100);
        strncpy(_nEle.m_strName, "3", 100);
        _pArrayParam->m_arrElements.Add(_nEle);

        // ElementAddress
        _nEleAddress.m_nPen.m_nColor = COLOR_9;
        _nEleAddress.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleAddress.m_nContent, "Addr+2", 100);
        _pArrayParam->m_arrElementAddresses.Add(_nEleAddress);

        // ElementIndex
        _nEleIndex.m_nPen.m_nColor = COLOR_9;
        _nEleIndex.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleIndex.m_nContent, "2", 100);
        _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
        _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
        _pArrayParam->m_arrElementIndexes.Add(_nEleIndex);

        // Element
        _nEle.m_nBrush.m_nColor = COLOR_5;
        _nEle.m_nPen.m_nColor = COLOR_9;
        _nEle.m_nPen.m_nWidth = 10.0;
        strncpy(_nEle.m_nContent, "4", 100);
        strncpy(_nEle.m_strName, "4", 100);
        _pArrayParam->m_arrElements.Add(_nEle);

        // ElementAddress
        _nEleAddress.m_nPen.m_nColor = COLOR_9;
        _nEleAddress.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleAddress.m_nContent, "Addr+3", 100);
        _pArrayParam->m_arrElementAddresses.Add(_nEleAddress);

        // ElementIndex
        _nEleIndex.m_nPen.m_nColor = COLOR_9;
        _nEleIndex.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleIndex.m_nContent, "3", 100);
        _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
        _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
        _pArrayParam->m_arrElementIndexes.Add(_nEleIndex);

        // ELement
        _nEle.m_nBrush.m_nColor = COLOR_6;
        _nEle.m_nPen.m_nColor = COLOR_9;
        _nEle.m_nPen.m_nWidth = 10.0;
        strncpy(_nEle.m_nContent, "5", 100);
        strncpy(_nEle.m_strName, "5", 100);
        _pArrayParam->m_arrElements.Add(_nEle);

        // ElementAddress
        _nEleAddress.m_nPen.m_nColor = COLOR_9;
        _nEleAddress.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleAddress.m_nContent, "Addr+4", 100);
        _pArrayParam->m_arrElementAddresses.Add(_nEleAddress);

        // ElementIndex
        _nEleIndex.m_nPen.m_nColor = COLOR_9;
        _nEleIndex.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleIndex.m_nContent, "4", 100);
        _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
        _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
        _pArrayParam->m_arrElementIndexes.Add(_nEleIndex);

        // ELement
        _nEle.m_nBrush.m_nColor = COLOR_11;
        _nEle.m_nPen.m_nColor = COLOR_9;
        _nEle.m_nPen.m_nWidth = 10.0;
        strncpy(_nEle.m_nContent, "", 100);
        strncpy(_nEle.m_strName, "", 100);
        _pArrayParam->m_arrElements.Add(_nEle);

        // ElementAddress
        _nEleAddress.m_nPen.m_nColor = COLOR_9;
        _nEleAddress.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleAddress.m_nContent, "Addr+5", 100);
        _pArrayParam->m_arrElementAddresses.Add(_nEleAddress);

        // ElementIndex
        _nEleIndex.m_nPen.m_nColor = COLOR_9;
        _nEleIndex.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleIndex.m_nContent, "5", 100);
        _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
        _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
        _pArrayParam->m_arrElementIndexes.Add(_nEleIndex);

        // ELement
        _nEle.m_nBrush.m_nColor = COLOR_11;
        _nEle.m_nPen.m_nColor = COLOR_9;
        _nEle.m_nPen.m_nWidth = 10.0;
        strncpy(_nEle.m_nContent, "", 100);
        strncpy(_nEle.m_strName, "", 100);
        _pArrayParam->m_arrElements.Add(_nEle);

        // ElementAddress
        _nEleAddress.m_nPen.m_nColor = COLOR_9;
        _nEleAddress.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleAddress.m_nContent, "Addr+6", 100);
        _pArrayParam->m_arrElementAddresses.Add(_nEleAddress);

        // ElementIndex
        _nEleIndex.m_nPen.m_nColor = COLOR_9;
        _nEleIndex.m_nPen.m_nWidth = 4.0;
        strncpy(_nEleIndex.m_nContent, "6", 100);
        _nEleIndex.m_nVerticalLen = _nEleIndex.m_nSize.m_nHeight;
        _nEleIndex.m_nHorizontalLen = _nEleIndex.m_nSize.m_nWidth / 4.0;
        _pArrayParam->m_arrElementIndexes.Add(_nEleIndex);

        s_nArrayParam = _pArrayParam;
        return s_nArrayParam;
    }
}
