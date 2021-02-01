//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arraymodelfileparse.h"

namespace NFileParse
{
    ArrayModelFileParse::ArrayModelFileParse(QObject *parent)
        : ModelFileParse(parent)
    {

    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::BuildModel(
            const NParameter::ArrayParameter& nParam_,
            NDataStruct::DynArray<NModel::Part*>& dynEleArr_,
            NDataStruct::DynArray<NModel::Part*>& dynEleBackGroundArr_,
            NDataStruct::DynArray<NModel::Part*>& dynEleAddrArr_,
            NDataStruct::DynArray<NModel::Part*>& dynEleIndexArr_)
    {
        ConstuctElementParts(nParam_, dynEleArr_, dynEleBackGroundArr_);
        ConstuctElementAddressParts(nParam_, dynEleAddrArr_);
        ConstuctElementIndexParts(nParam_, dynEleIndexArr_);
        return SUCCESS;
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::ParseFile(
            const QString& strFilePath_,
            NParameter::ArrayParameter& nParam_)
    {
        m_file.close();
        m_file.setFileName(strFilePath_);
        bool _bRet = m_file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly);
        if(!_bRet)
        {
            return FILE_NOT_EXIST;
        }

        FILE_PARSE_RET_CODE _nRetCode = SUCCESS;
        NParameter::ArrayParameter _nParam;
        _nRetCode = ReadArrayModel(0);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }

        _nRetCode = ReadArray(0, _nParam);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }

        for(int i = 0; i < _nParam.m_nCapacity; i++)
        {
            NParameter::Element _nEle;
            _nRetCode = ReadElement(_nEle);
            if(i < _nParam.m_nSize)
            {
                _nParam.m_arrElements.Add(_nEle);
            }

            if(_nRetCode != SUCCESS)
            {
                return _nRetCode;
            }

            NParameter::ElementAddress _nEleAddress;
            _nRetCode = ReadElementAddress(_nEleAddress);
            _nParam.m_arrElementAddresses.Add(_nEleAddress);
            if(_nRetCode != SUCCESS)
            {
                return _nRetCode;
            }

            NParameter::ElementIndex _nEleIndex;
            _nRetCode = ReadElementIndex(_nEleIndex);
            _nParam.m_arrElementIndexes.Add(_nEleIndex);
            if(_nRetCode != SUCCESS)
            {
                return _nRetCode;
            }
        }

        _nRetCode = ReadArray(1, _nParam);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }

        _nRetCode = ReadArrayModel(1);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }

        nParam_ = _nParam;
        return SUCCESS;
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::Parse(
            const QString& strFilePath_,
            NDataStruct::DynArray<NModel::Part*>& dynEleArr_,
            NDataStruct::DynArray<NModel::Part*>& dynEleBackGroundArr_,
            NDataStruct::DynArray<NModel::Part*>& dynEleAddrArr_,
            NDataStruct::DynArray<NModel::Part*>& dynEleIndexArr_)
    {
        m_file.close();
        m_file.setFileName(strFilePath_);
        bool _bRet = m_file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly);
        if(!_bRet)
        {
            return FILE_NOT_EXIST;
        }

        FILE_PARSE_RET_CODE _nRetCode = SUCCESS;
        NParameter::ArrayParameter _nParam;
        _nRetCode = ReadArrayModel(0);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }

        _nRetCode = ReadArray(0, _nParam);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }

        for(int i = 0; i < _nParam.m_nCapacity; i++)
        {
            NParameter::Element _nEle;
            _nRetCode = ReadElement(_nEle);
            _nParam.m_arrElements.Add(_nEle);
            if(_nRetCode != SUCCESS)
            {
                return _nRetCode;
            }

            NParameter::ElementAddress _nEleAddress;
            _nRetCode = ReadElementAddress(_nEleAddress);
            _nParam.m_arrElementAddresses.Add(_nEleAddress);
            if(_nRetCode != SUCCESS)
            {
                return _nRetCode;
            }

            NParameter::ElementIndex _nEleIndex;
            _nRetCode = ReadElementIndex(_nEleIndex);
            _nParam.m_arrElementIndexes.Add(_nEleIndex);
            if(_nRetCode != SUCCESS)
            {
                return _nRetCode;
            }
        }

        _nRetCode = ReadArray(1, _nParam);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }

        _nRetCode = ReadArrayModel(1);
        if(_nRetCode != SUCCESS)
        {
            return _nRetCode;
        }


        ConstuctElementParts(_nParam, dynEleArr_, dynEleBackGroundArr_);
        ConstuctElementAddressParts(_nParam, dynEleAddrArr_);
        ConstuctElementIndexParts(_nParam, dynEleIndexArr_);
        return SUCCESS;
    }

    void ArrayModelFileParse::ConstuctElementParts(
            const NParameter::ArrayParameter& nParam_,
            NDataStruct::DynArray<NModel::Part*>& dynArr_,
            NDataStruct::DynArray<NModel::Part*>& dynBackGroundArr_)
    {
        for(int i = 0; i < nParam_.m_nCapacity; i++)
        {
            if(i < nParam_.m_nSize)
            {
                // construct a valued part
                NModel::ArrayPart* _pPart = new NModel::ArrayPart(NModel::ELEMENT);
                 NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(i * nParam_.m_nElementSize.m_nWidth, 0.0, _pPart);
                _pPart->SetInitialTransform(_pTrans);
                NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
                _pDrawing->setParent(_pPart);

                NParameter::Element _nEle = nParam_.m_arrElements[i];

                _pPart->SetName(_nEle.m_strName);
                _pPart->SetPosition(_nEle.m_nPosition);

                QPen _nPen = NParameter::GetPen(_nEle.m_nPen.m_nColor, _nEle.m_nPen.m_nWidth);
                QBrush _nBrush;
                _nBrush = NParameter::GetBrush(_nEle.m_nBrush.m_nColor);
                QString _str(_nEle.m_nFont.m_strFamily);
                QFont _nFont(_str, _nEle.m_nFont.m_nPointSize, _nEle.m_nFont.m_nWeight, _nEle.m_nFont.m_bItalic);
                // setting part's pen
                _pDrawing->SetPen(_nPen);
                // setting part's brush
                _pDrawing->SetBrush(_nBrush);
                _pDrawing->SetFont(_nFont);

                NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
                NStruct::Rect _nRect;
                _nRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
                _nRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
                NGeometry::GeometryRect* _pRectGeo = new NGeometry::GeometryRect(_nRect, _pGeoGroup);

                QByteArray _arrByte(nParam_.m_arrElements[i].m_nContent, strlen(nParam_.m_arrElements[i].m_nContent));
                NGeometry::GeometryText* _pTextGeo = new NGeometry::GeometryText(_arrByte, _nRect, Qt::AlignCenter, _pGeoGroup);
                _pGeoGroup->Add(_pRectGeo);
                _pGeoGroup->Add(_pTextGeo);
                _pDrawing->SetGeometry(_pGeoGroup);


                _pPart->SetDrawing(_pDrawing);
                dynArr_.Add(_pPart);
            }


            {
                // construct a non-value part
                NModel::MovablePart* _pPart = new NModel::MovablePart();
                NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(
                            i * nParam_.m_nElementSize.m_nWidth,
                            0.0,
                            _pPart);
                _pPart->SetInitialTransform(_pTrans);
                NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
                _pDrawing->setParent(_pPart);

                QPen _nPen = NParameter::GetPen(
                            nParam_.m_nPen.m_nColor,
                            nParam_.m_nPen.m_nWidth);
                QBrush _nBrush;
                _nBrush = NParameter::GetBrush(
                            nParam_.m_nBrush.m_nColor);
                QString _str(nParam_.m_nFont.m_strFamily);
                QFont _nFont(_str,
                             nParam_.m_nFont.m_nPointSize,
                             nParam_.m_nFont.m_nWeight,
                             nParam_.m_nFont.m_bItalic);
                // setting part's pen
                _pDrawing->SetPen(_nPen);
                // setting part's brush
                _pDrawing->SetBrush(_nBrush);
                _pDrawing->SetFont(_nFont);

                NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
                NStruct::Rect _nRect;
                _nRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
                _nRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
                NGeometry::GeometryRect* _pRectGeo = new NGeometry::GeometryRect(_nRect, _pGeoGroup);
                _pGeoGroup->Add(_pRectGeo);
                _pDrawing->SetGeometry(_pGeoGroup);
                _pPart->SetDrawing(_pDrawing);
                dynBackGroundArr_.Add(_pPart);
            }
        }
    }

    void ArrayModelFileParse::ConstuctElementAddressParts(
            const NParameter::ArrayParameter& nParam_,
            NDataStruct::DynArray<NModel::Part*>& dynEleAddrArr_)
    {
        for(int i = 0; i < nParam_.m_nCapacity; i++)
        {
            if(true)
            {
                // construct a ElementAddress
                NModel::ArrayPart* _pPart = new NModel::ArrayPart(NModel::ELEMENT_ADDRESS);
                NTransform::TransformGroup* _pTransGroup = new NTransform::TransformGroup(_pPart);
                NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(
                            i * nParam_.m_nElementSize.m_nWidth, 0.0, _pTransGroup);
                _pTransGroup->Add(_pTrans);
                NTransform::LinearTransform* _pLinearTrans = new NTransform::LinearTransform(
                            0.0,
                            -nParam_.m_nElementSize.m_nHeight - 10,
                            _pTransGroup);
                _pTransGroup->Add(_pLinearTrans);
                _pPart->SetInitialTransform(_pTransGroup);

                NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
                _pDrawing->setParent(_pPart);

                NParameter::ElementAddress _nEleAddr = nParam_.m_arrElementAddresses[i];
                QPen _nPen = NParameter::GetPen(_nEleAddr.m_nPen.m_nColor, _nEleAddr.m_nPen.m_nWidth);
                QBrush _nBrush;
                _nBrush = NParameter::GetBrush(_nEleAddr.m_nBrush.m_nColor);
                QString _str(_nEleAddr.m_nFont.m_strFamily);
                QFont _nFont(_str, _nEleAddr.m_nFont.m_nPointSize, _nEleAddr.m_nFont.m_nWeight, _nEleAddr.m_nFont.m_bItalic);
                // setting part's pen
                _pDrawing->SetPen(_nPen);
                // setting part's brush
                _pDrawing->SetBrush(_nBrush);
                _pDrawing->SetFont(_nFont);

                NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
                //NStruct::Rect _nRect;
                //_nRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
                //_nRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
                NStruct::Line _nLine;
                double _nAngle = (180.0 + 45.0) / 180.0 * PI;
                _nLine.SetStart(NStruct::Point(_nEleAddr.m_nArrowLen1*  cos(_nAngle), _nEleAddr.m_nArrowLen1 * sin(_nAngle)));
                _nLine.SetEnd(NStruct::Point());
                NGeometry::GeometryLine* _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);
                _nAngle = (270.0 + 45.0) / 180.0 * PI;
                _nLine.SetStart(NStruct::Point(_nEleAddr.m_nArrowLen1*  cos(_nAngle), _nEleAddr.m_nArrowLen1 * sin(_nAngle)));
                _nLine.SetEnd(NStruct::Point());
                _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);

                _nAngle = (270.0) / 180.0 * PI;
                _nLine.SetStart(NStruct::Point(_nEleAddr.m_nArrowLen2*  cos(_nAngle), _nEleAddr.m_nArrowLen2 * sin(_nAngle)));
                _nLine.SetEnd(NStruct::Point());
                _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);
                //NGeometry::GeometryRect* _pRectGeo = new NGeometry::GeometryRect(_nRect, _pGeoGroup);

                NStruct::Rect _rcRect;
                _rcRect.SetLeftUp(NStruct::Point(-1 * nParam_.m_nElementSize.m_nWidth / 2.0, -_nEleAddr.m_nArrowLen2));
                _rcRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
                _rcRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
                QByteArray _arrByte(nParam_.m_arrElementAddresses[i].m_nContent, strlen(nParam_.m_arrElementAddresses[i].m_nContent));
                NGeometry::GeometryText* _pTextGeo = new NGeometry::GeometryText(_arrByte, _rcRect, Qt::AlignTop | Qt::AlignHCenter, _pGeoGroup);
                _pGeoGroup->Add(_pTextGeo);
                _pDrawing->SetGeometry(_pGeoGroup);

                _pPart->SetDrawing(_pDrawing);
                dynEleAddrArr_.Add(_pPart);
            }
            else
            {
                // construct a non-value part
                /*NModel::MovablePart* _pPart = new NModel::MovablePart();
                NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(i * nParam_.m_nElementSize.m_nWidth, 0.0, _pPart);
                _pPart->SetInitialTransform(_pTrans);
                NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
                _pDrawing->setParent(_pPart);

                QPen _nPen = NParameter::GetPen(nParam_.m_nPen.m_nColor, nParam_.m_nPen.m_nWidth);
                QBrush _nBrush;
                _nBrush = NParameter::GetBrush(nParam_.m_nBrush.m_nColor);
                QString _str(nParam_.m_nFont.m_strFamily);
                QFont _nFont(_str, nParam_.m_nFont.m_nPointSize, nParam_.m_nFont.m_nWeight, nParam_.m_nFont.m_bItalic);
                // setting part's pen
                _pDrawing->SetPen(_nPen);
                // setting part's brush
                _pDrawing->SetBrush(_nBrush);
                _pDrawing->SetFont(_nFont);

                NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
                NStruct::Rect _nRect;
                _nRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
                _nRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
                NGeometry::GeometryRect* _pRectGeo = new NGeometry::GeometryRect(_nRect, _pGeoGroup);

                _pGeoGroup->Add(_pRectGeo);
                _pDrawing->SetGeometry(_pGeoGroup);
                _pPart->SetDrawing(_pDrawing);
                dynArr_.Add(_pPart);*/
            }
        }
    }

    void ArrayModelFileParse::ConstuctElementIndexParts(
            const NParameter::ArrayParameter& nParam_,
            NDataStruct::DynArray<NModel::Part*>& dynEleIndexArr_)
    {
        for(int i = 0; i < nParam_.m_nCapacity; i++)
        {
            if(true)
            {
                // construct a ElementIndex
                NModel::ArrayPart* _pPart = new NModel::ArrayPart(NModel::ELEMENT_INDEX);
                NTransform::TransformGroup* _pTransGroup = new NTransform::TransformGroup(_pPart);
                NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(
                            i * nParam_.m_nElementSize.m_nWidth,
                            0.0,
                            _pTransGroup);
                _pTransGroup->Add(_pTrans);
                _pTrans = new NTransform::LinearTransform(
                            nParam_.m_nElementSize.m_nWidth / 2.0,
                            -nParam_.m_nElementSize.m_nHeight - 10,
                            _pTransGroup);
                _pTransGroup->Add(_pTrans);
                _pPart->SetInitialTransform(_pTransGroup);

                NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
                _pDrawing->setParent(_pPart);

                NParameter::ElementIndex _nEleIndex = nParam_.m_arrElementIndexes[i];
                QPen _nPen = NParameter::GetPen(_nEleIndex.m_nPen.m_nColor, _nEleIndex.m_nPen.m_nWidth);
                QBrush _nBrush;
                _nBrush = NParameter::GetBrush(_nEleIndex.m_nBrush.m_nColor);
                QString _str(_nEleIndex.m_nFont.m_strFamily);
                QFont _nFont(_str, _nEleIndex.m_nFont.m_nPointSize, _nEleIndex.m_nFont.m_nWeight, _nEleIndex.m_nFont.m_bItalic);
                // setting part's pen
                _pDrawing->SetPen(_nPen);
                // setting part's brush
                _pDrawing->SetBrush(_nBrush);
                _pDrawing->SetFont(_nFont);

                NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
                //NStruct::Rect _nRect;
                //_nRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
                //_nRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
                NStruct::Line _nLine;
                //double _nAngle = (180.0) / 180.0 * PI;
                _nLine.SetStart(NStruct::Point(-_nEleIndex.m_nSize.m_nWidth / 2.0, 0.0));
                _nLine.SetEnd(NStruct::Point(-_nEleIndex.m_nSize.m_nWidth / 2.0 + _nEleIndex.m_nHorizontalLen, 0.0));
                NGeometry::GeometryLine* _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);
                _nLine.SetStart(NStruct::Point(-_nEleIndex.m_nSize.m_nWidth / 2.0 , 0.0));
                _nLine.SetEnd(NStruct::Point(-_nEleIndex.m_nSize.m_nWidth / 2.0, -_nEleIndex.m_nSize.m_nHeight));
                _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);
                _nLine.SetStart(NStruct::Point(-_nEleIndex.m_nSize.m_nWidth / 2.0 , -_nEleIndex.m_nSize.m_nHeight));
                _nLine.SetEnd(NStruct::Point(-_nEleIndex.m_nSize.m_nWidth / 2.0 + _nEleIndex.m_nHorizontalLen,
                                             -_nEleIndex.m_nSize.m_nHeight));
                _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);


                _nLine.SetStart(NStruct::Point(_nEleIndex.m_nSize.m_nWidth / 2.0 - _nEleIndex.m_nHorizontalLen, 0.0));
                _nLine.SetEnd(NStruct::Point(_nEleIndex.m_nSize.m_nWidth / 2.0 , 0.0));
                _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);
                _nLine.SetStart(NStruct::Point(_nEleIndex.m_nSize.m_nWidth / 2.0, 0.0));
                _nLine.SetEnd(NStruct::Point(_nEleIndex.m_nSize.m_nWidth / 2.0, -_nEleIndex.m_nSize.m_nHeight));
                _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);
                _nLine.SetStart(NStruct::Point(_nEleIndex.m_nSize.m_nWidth / 2.0, -_nEleIndex.m_nSize.m_nHeight));
                _nLine.SetEnd(NStruct::Point(_nEleIndex.m_nSize.m_nWidth / 2.0 - _nEleIndex.m_nHorizontalLen,
                                             -_nEleIndex.m_nSize.m_nHeight));
                _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
                _pGeoGroup->Add(_pLineGeo);

                NStruct::Rect _rcRect;
                _rcRect.SetLeftUp(NStruct::Point(-1 * _nEleIndex.m_nSize.m_nWidth / 2.0, 0.0));
                _rcRect.SetHeight(_nEleIndex.m_nSize.m_nHeight);
                _rcRect.SetWeight(_nEleIndex.m_nSize.m_nWidth);
                QByteArray _arrByte(nParam_.m_arrElementIndexes[i].m_nContent, strlen(nParam_.m_arrElementIndexes[i].m_nContent));
                NGeometry::GeometryText* _pTextGeo = new NGeometry::GeometryText(_arrByte, _rcRect, Qt::AlignTop|Qt::AlignHCenter, _pGeoGroup);
                _pGeoGroup->Add(_pTextGeo);
                _pDrawing->SetGeometry(_pGeoGroup);

                _pPart->SetDrawing(_pDrawing);
                dynEleIndexArr_.Add(_pPart);
            }
            else
            {
                // construct a non-value part
                /*NModel::MovablePart* _pPart = new NModel::MovablePart();
                NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(i * nParam_.m_nElementSize.m_nWidth, 0.0, _pPart);
                _pPart->SetInitialTransform(_pTrans);
                NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
                _pDrawing->setParent(_pPart);

                QPen _nPen = NParameter::GetPen(nParam_.m_nPen.m_nColor, nParam_.m_nPen.m_nWidth);
                QBrush _nBrush;
                _nBrush = NParameter::GetBrush(nParam_.m_nBrush.m_nColor);
                QString _str(nParam_.m_nFont.m_strFamily);
                QFont _nFont(_str, nParam_.m_nFont.m_nPointSize, nParam_.m_nFont.m_nWeight, nParam_.m_nFont.m_bItalic);
                // setting part's pen
                _pDrawing->SetPen(_nPen);
                // setting part's brush
                _pDrawing->SetBrush(_nBrush);
                _pDrawing->SetFont(_nFont);

                NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
                NStruct::Rect _nRect;
                _nRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
                _nRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
                NGeometry::GeometryRect* _pRectGeo = new NGeometry::GeometryRect(_nRect, _pGeoGroup);

                _pGeoGroup->Add(_pRectGeo);
                _pDrawing->SetGeometry(_pGeoGroup);
                _pPart->SetDrawing(_pDrawing);
                dynArr_.Add(_pPart);*/
            }
        }
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::ReadArrayModel(int nFlag_)
    {
        if(nFlag_ == 0)
        {
            QByteArray _arrByte = m_file.readLine();
            if(_arrByte.isEmpty())
            {
                return EMPTY_FILE;
            }

            int _nRet = _arrByte.indexOf("ArrayModel", 0);
            if(_nRet == -1)
            {
                return FILE_FORMAT_ERR_FIRST_LINE_NOT_ARRAYMODEL;
            }

            return SUCCESS;
        }
        else
        {
            QByteArray _arrByte = m_file.readLine();
            if(_arrByte.isEmpty())
            {
                return EMPTY_FILE;
            }

            int _nRet = _arrByte.indexOf("ArrayModel", 0);
            if(_nRet == -1)
            {
                return FILE_FORMAT_ERR_UNREAD_ARRAYMODEL_END;
            }

            return SUCCESS;
        }
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::GetInt(
        const QByteArray& arrByte_,
        int nIndex_,
        const char* strSep1_,
        const char* strSep2_,
        int& nRet_)
    {
        int _nSIndex = arrByte_.indexOf(strSep1_, nIndex_);
        if(_nSIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        _nSIndex++;
        int _nEIndex = arrByte_.indexOf(strSep2_, _nSIndex);
        if(_nEIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        QByteArray _arrTemp = arrByte_.mid(_nSIndex, _nEIndex - _nSIndex);
        bool _bRet;
        long _nValue = _arrTemp.toInt(&_bRet);
        if(!_bRet)
        {
            return FILE_FORMAT_ERR;
        }

        nRet_ = _nValue;
        return SUCCESS;
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::GetDouble(
        const QByteArray& arrByte_,
        int nIndex_,
        const char* strSep1_,
        const char* strSep2_,
        double& nRet_)
    {
        int _nSIndex = arrByte_.indexOf(strSep1_, nIndex_);
        if(_nSIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        _nSIndex++;
        int _nEIndex = arrByte_.indexOf(strSep2_, _nSIndex);
        if(_nEIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        QByteArray _arrTemp = arrByte_.mid(_nSIndex, _nEIndex - _nSIndex);
        bool _bRet;
        long _nValue = _arrTemp.toDouble(&_bRet);
        if(!_bRet)
        {
            return FILE_FORMAT_ERR;
        }

        nRet_ = _nValue;
        return SUCCESS;
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::GetString(
        const QByteArray& arrByte_,
        int nIndex_,
        const char* strSep1_,
        const char* strSep2_,
        QByteArray& nByteArr_)
    {
        int _nSIndex = arrByte_.indexOf(strSep1_, nIndex_);
        if(_nSIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        _nSIndex++;
        int _nEIndex = arrByte_.indexOf(strSep2_, _nSIndex);
        if(_nEIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        QByteArray _arrTemp = arrByte_.mid(_nSIndex, _nEIndex - _nSIndex);
        nByteArr_ = _arrTemp;
        return SUCCESS;
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::ReadArray(int nFlag_, NParameter::ArrayParameter& nParam_)
    {
        NParameter::ArrayParameter _nCopy = nParam_;
        if(nFlag_ == 0)
        {
            QByteArray _arrByte = m_file.readLine();
            if(_arrByte.isEmpty())
            {
                return FILE_FORMAT_ERR_UNREAD_EXPECTED_ELEMENT;
            }

            int _nIndex = _arrByte.indexOf("Array", 0);
            if(_nIndex == -1)
            {
                return FILE_FORMAT_ERR;
            }

            // read Capacity
            _nIndex = _arrByte.indexOf("Capacity", 0);
            if(_nIndex != -1)
            {
               FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nCopy.m_nCapacity);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Size
            _nIndex = _arrByte.indexOf("Size", 0);
            if(_nIndex != -1)
            {

               FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nCopy.m_nSize);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read ElementSize.Width
            _nIndex = _arrByte.indexOf("ElementSize.Width", 0);
            if(_nIndex != -1)
            {

               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nCopy.m_nElementSize.m_nWidth);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read ElemntSize.Height
            _nIndex = _arrByte.indexOf("ElementSize.Height", 0);
            if(_nIndex != -1)
            {

               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nCopy.m_nElementSize.m_nHeight);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Pen.Color
            _nIndex = _arrByte.indexOf("Pen.Color", 0);
            if(_nIndex != -1)
            {
               int _nColor;
               FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

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

               if(_nColor >= 0 && _nColor < _arrColors.GetSize())
               {
                    _nCopy.m_nPen.m_nColor = _arrColors[_nColor];
               }

            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Pen.Width
            _nIndex = _arrByte.indexOf("Pen.Width", 0);
            if(_nIndex != -1)
            {

               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nCopy.m_nPen.m_nWidth);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }


            // read Point.X
            _nIndex = _arrByte.indexOf("Point.X", 0);
            if(_nIndex != -1)
            {
               double _nX;
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nX);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

               _nCopy.m_poStart.SetX(_nX);
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Point.Y
            _nIndex = _arrByte.indexOf("Point.Y", 0);
            if(_nIndex != -1)
            {
               double _nY;
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nY);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

               _nCopy.m_poStart.SetY(_nY);
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Brush.Color
            _nIndex = _arrByte.indexOf("Brush.Color", 0);
            if(_nIndex != -1)
            {
               int _nColor;
               FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

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

               if(_nColor >= 0 && _nColor < _arrColors.GetSize())
               {
                    _nCopy.m_nBrush.m_nColor = _arrColors[_nColor];
               }

            }
            else
            {
                return FILE_FORMAT_ERR;
            }


            // read Font.Family
            _nIndex = _arrByte.indexOf("Font.Family", 0);
            if(_nIndex != -1)
            {
               QByteArray _nArr;
               FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

               strncpy(_nCopy.m_nFont.m_strFamily, _nArr.data(), sizeof(_nCopy.m_nFont.m_strFamily));
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Font.PointSize
            _nIndex = _arrByte.indexOf("Font.PointSize", 0);
            if(_nIndex != -1)
            {
               FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nCopy.m_nFont.m_nPointSize);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Font.Weight
            _nIndex = _arrByte.indexOf("Font.Weight", 0);
            if(_nIndex != -1)
            {
               FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nCopy.m_nFont.m_nWeight);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Font.Italic
            _nIndex = _arrByte.indexOf("Font.Italic", 0);
            if(_nIndex != -1)
            {
               int _nItalic;
               FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nItalic);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

               _nCopy.m_nFont.m_bItalic = _nItalic == 0 ? false : true;
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            nParam_ = _nCopy;
            return SUCCESS;
        }
        else
        {
            QByteArray _arrByte = m_file.readLine();
            if(_arrByte.isEmpty())
            {
                return FILE_FORMAT_ERR_UNREAD_EXPECTED_ELEMENT;
            }

            int _nIndex = _arrByte.indexOf("Array", 0);
            if(_nIndex == -1)
            {
                return FILE_FORMAT_ERR;
            }

            return SUCCESS;
        }
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::ReadElement(NParameter::Element& nEle_)
    {
        NParameter::Element _nEle = nEle_;
        QByteArray _arrByte = m_file.readLine();
        if(_arrByte.isEmpty())
        {
            return FILE_FORMAT_ERR;
        }

        int _nIndex = _arrByte.indexOf("Element", 0);
        if(_nIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        // read Content
        _nIndex = _arrByte.indexOf("Content", 0);
        if(_nIndex != -1)
        {

           QByteArray _nArr;
           FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           strncpy(_nEle.m_nContent, _nArr.data(), sizeof(_nEle.m_nContent));
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read name
        _nIndex = _arrByte.indexOf("Name", 0);
        if(_nIndex != -1)
        {
           QByteArray _nArr;
           FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           strncpy(_nEle.m_strName, _nArr.data(), sizeof(_nEle.m_strName));
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Brush.Color
        _nIndex = _arrByte.indexOf("Brush.Color", 0);
        if(_nIndex != -1)
        {
           int _nColor;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

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

           if(_nColor >= 0 && _nColor < _arrColors.GetSize())
           {
                _nEle.m_nBrush.m_nColor = _arrColors[_nColor];
           }

        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Pen.Color
        _nIndex = _arrByte.indexOf("Pen.Color", 0);
        if(_nIndex != -1)
        {
           int _nColor;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

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

           if(_nColor >= 0 && _nColor < _arrColors.GetSize())
           {
                _nEle.m_nPen.m_nColor = _arrColors[_nColor];
           }

        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Pen.Width
        _nIndex = _arrByte.indexOf("Pen.Width", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEle.m_nPen.m_nWidth);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Family
        _nIndex = _arrByte.indexOf("Font.Family", 0);
        if(_nIndex != -1)
        {
           QByteArray _nArr;
           FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           strncpy(_nEle.m_nFont.m_strFamily, _nArr.data(), sizeof(_nEle.m_nFont.m_strFamily));
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Font.PointSize
        _nIndex = _arrByte.indexOf("Font.PointSize", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nEle.m_nFont.m_nPointSize);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Font.Weight
        _nIndex = _arrByte.indexOf("Font.Weight", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nEle.m_nFont.m_nWeight);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Font.Italic
        _nIndex = _arrByte.indexOf("Font.Italic", 0);
        if(_nIndex != -1)
        {
           int _nItalic;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nItalic);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           _nEle.m_nFont.m_bItalic = _nItalic == 0 ? false : true;
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Move_Type
        _nIndex = _arrByte.indexOf("MoveType", 0);
        if(_nIndex != -1)
        {
           int _nMoveType;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nMoveType);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           _nEle.m_nPosition.m_nMoveType = (NModel::MOVE_TYPE)_nMoveType;
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        if(_nEle.m_nPosition.m_nMoveType == NModel::MOVE_TYPE::LINEAR)
        {
            // read CurPos
            _nIndex = _arrByte.indexOf("CurPos", 0);
            if(_nIndex != -1)
            {
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEle.m_nPosition.m_nPosition.m_nLinearPos.m_nCurPosition);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // read Font.Weight
            _nIndex = _arrByte.indexOf("Angle", 0);
            if(_nIndex != -1)
            {
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEle.m_nPosition.m_nPosition.m_nLinearPos.m_nAngle);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }
        }
        else if(_nEle.m_nPosition.m_nMoveType == NModel::MOVE_TYPE::ROTATE)
        {
            // CenterX
            _nIndex = _arrByte.indexOf("CenterX", 0);
            if(_nIndex != -1)
            {
               double _nX;
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nX);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

               _nEle.m_nPosition.m_nPosition.m_nRotatePos.m_poCenter.SetX(_nX);
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // CenterY
            _nIndex = _arrByte.indexOf("CenterY", 0);
            if(_nIndex != -1)
            {
               double _nY;
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nY);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

               _nEle.m_nPosition.m_nPosition.m_nRotatePos.m_poCenter.SetY(_nY);
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // Radius
            _nIndex = _arrByte.indexOf("Radius", 0);
            if(_nIndex != -1)
            {
               double _nRadius;
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nRadius);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }

               _nEle.m_nPosition.m_nPosition.m_nRotatePos.m_nRadius = _nRadius;
            }
            else
            {
                return FILE_FORMAT_ERR;
            }

            // Angle
            _nIndex = _arrByte.indexOf("Angle", 0);
            if(_nIndex != -1)
            {
               FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEle.m_nPosition.m_nPosition.m_nRotatePos.m_nAngle);
               if(_nRet != SUCCESS)
               {
                   return _nRet;
               }
            }
            else
            {
                return FILE_FORMAT_ERR;
            }
        }
        else
        {
            assert(false);
        }

        nEle_ = _nEle;
        return SUCCESS;
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::ReadElementAddress(NParameter::ElementAddress& nEleAddress_)
    {
        NParameter::ElementAddress _nEleAddress = nEleAddress_;
        QByteArray _arrByte = m_file.readLine();
        if(_arrByte.isEmpty())
        {
            return FILE_FORMAT_ERR;
        }

        int _nIndex = _arrByte.indexOf("ElementAddress", 0);
        if(_nIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        // read ArrowLen1
        _nIndex = _arrByte.indexOf("ArrowLen1", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleAddress.m_nArrowLen1);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read ArrowLen2
        _nIndex = _arrByte.indexOf("ArrowLen2", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleAddress.m_nArrowLen2);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Size.Height
        _nIndex = _arrByte.indexOf("Size.Height", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleAddress.m_nSize.m_nHeight);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Size.Weight
        _nIndex = _arrByte.indexOf("Size.Width", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleAddress.m_nSize.m_nWidth);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Family
        _nIndex = _arrByte.indexOf("Content", 0);
        if(_nIndex != -1)
        {
           QByteArray _nArr;
           FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           strncpy(_nEleAddress.m_nContent, _nArr.data(), sizeof(_nEleAddress.m_nContent));
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Font.PointSize
        _nIndex = _arrByte.indexOf("Pen.Color", 0);
        if(_nIndex != -1)
        {
           int _nColor;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

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
           if(_nColor >= 0 && _nColor < _arrColors.GetSize())
           {
                _nEleAddress.m_nPen.m_nColor = _arrColors[_nColor];
           }

        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Pen.Width
        _nIndex = _arrByte.indexOf("Pen.Width", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleAddress.m_nPen.m_nWidth);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Brush.Color
        _nIndex = _arrByte.indexOf("Brush.Color", 0);
        if(_nIndex != -1)
        {
           int _nColor;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

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
           if(_nColor >= 0 && _nColor < _arrColors.GetSize())
           {
                _nEleAddress.m_nBrush.m_nColor = _arrColors[_nColor];
           }

        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Family
        _nIndex = _arrByte.indexOf("Font.Family", 0);
        if(_nIndex != -1)
        {
           QByteArray _nArr;
           FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           strncpy(_nEleAddress.m_nFont.m_strFamily, _nArr.data(), sizeof(_nEleAddress.m_nFont.m_strFamily));
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.PointSize
        _nIndex = _arrByte.indexOf("Font.PointSize", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nEleAddress.m_nFont.m_nPointSize);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Weight
        _nIndex = _arrByte.indexOf("Font.Weight", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nEleAddress.m_nFont.m_nWeight);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Italic
        _nIndex = _arrByte.indexOf("Font.Italic", 0);
        if(_nIndex != -1)
        {
           int _nItalic;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nItalic);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           _nEleAddress.m_nFont.m_bItalic = _nItalic == 0 ? false : true;
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        nEleAddress_ = _nEleAddress;
        return SUCCESS;
    }

    FILE_PARSE_RET_CODE ArrayModelFileParse::ReadElementIndex(NParameter::ElementIndex& nEleIndex_)
    {
        NParameter::ElementIndex _nEleIndex = nEleIndex_;
        QByteArray _arrByte = m_file.readLine();
        if(_arrByte.isEmpty())
        {
            return FILE_FORMAT_ERR;
        }


        int _nIndex = _arrByte.indexOf("ElementIndex", 0);
        if(_nIndex == -1)
        {
            return FILE_FORMAT_ERR;
        }

        // read HorizontalLen
        _nIndex = _arrByte.indexOf("HorizontalLen", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleIndex.m_nHorizontalLen);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read VerticalLen
        _nIndex = _arrByte.indexOf("VerticalLen", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleIndex.m_nVerticalLen);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Size.Height
        _nIndex = _arrByte.indexOf("Size.Height", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleIndex.m_nSize.m_nHeight);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Size.Width
        _nIndex = _arrByte.indexOf("Size.Width", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleIndex.m_nSize.m_nWidth);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Content
        _nIndex = _arrByte.indexOf("Content", 0);
        if(_nIndex != -1)
        {
           QByteArray _nArr;
           FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           strncpy(_nEleIndex.m_nContent, _nArr.data(), sizeof(_nEleIndex.m_nContent));
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Pen.Color
        _nIndex = _arrByte.indexOf("Pen.Color", 0);
        if(_nIndex != -1)
        {
           int _nColor;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

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

           if(_nColor >= 0 && _nColor < _arrColors.GetSize())
           {
                _nEleIndex.m_nPen.m_nColor = _arrColors[_nColor];
           }

        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Pen.Width
        _nIndex = _arrByte.indexOf("Pen.Width", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetDouble(_arrByte, _nIndex++, "=", ",", _nEleIndex.m_nPen.m_nWidth);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // read Brush.Color
        _nIndex = _arrByte.indexOf("Brush.Color", 0);
        if(_nIndex != -1)
        {
           int _nColor;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nColor);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

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

           if(_nColor >= 0 && _nColor < _arrColors.GetSize())
           {
                _nEleIndex.m_nBrush.m_nColor = _arrColors[_nColor];
           }

        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Family
        _nIndex = _arrByte.indexOf("Font.Family", 0);
        if(_nIndex != -1)
        {
           QByteArray _nArr;
           FILE_PARSE_RET_CODE _nRet = GetString(_arrByte, _nIndex++, "\"", "\"", _nArr);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           strncpy(_nEleIndex.m_nFont.m_strFamily, _nArr.data(), sizeof(_nEleIndex.m_nFont.m_strFamily));
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.PointSize
        _nIndex = _arrByte.indexOf("Font.PointSize", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nEleIndex.m_nFont.m_nPointSize);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Weight
        _nIndex = _arrByte.indexOf("Font.Weight", 0);
        if(_nIndex != -1)
        {
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nEleIndex.m_nFont.m_nWeight);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        // Font.Italic
        _nIndex = _arrByte.indexOf("Font.Italic", 0);
        if(_nIndex != -1)
        {
           int _nItalic;
           FILE_PARSE_RET_CODE _nRet = GetInt(_arrByte, _nIndex++, "=", ",", _nItalic);
           if(_nRet != SUCCESS)
           {
               return _nRet;
           }

           _nEleIndex.m_nFont.m_bItalic = _nItalic == 0 ? false : true;
        }
        else
        {
            return FILE_FORMAT_ERR;
        }

        nEleIndex_ = _nEleIndex;
        return SUCCESS;
    }

}

