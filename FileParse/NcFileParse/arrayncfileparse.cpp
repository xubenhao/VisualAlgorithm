//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayncfileparse.h"

namespace NFileParse
{
    bool operator==(const MoveObj& nObj1_, const MoveObj& nObj2_)
    {
        if(strcmp(nObj1_.m_strObjName, nObj2_.m_strObjName) == 0
            && nObj1_.m_nCurPos == nObj2_.m_nCurPos)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const MoveObj& nObj1_, const MoveObj& nObj2_)
    {
        return !operator==(nObj1_, nObj2_);
    }

    ArrayModalData::ArrayModalData()
    {

    }

    ArrayModalData::~ArrayModalData()
    {

    }

    ArrayNcFileParse::ArrayNcFileParse(
        const QString& strFilePath_,
        const NParameter::ArrayNcParameter& nParam_,
        const ArrayModalData& nModalData_,
        QObject* pParent_)
        : NcFileParse(pParent_)
    {
        m_file.close();
        m_file.setFileName(strFilePath_);
        bool _bFlag = m_file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly);
        if(!_bFlag)
        {
            m_nErrCode = NCFILE_PARSE_RET_CODE::NC_FILE_NOT_EXIST;
        }

        m_nParam = nParam_;
        m_nModalData = nModalData_;
    }

    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetNcCode(NNcCode::NcCode** ppNcCode_)
    {
        QByteArray _arrByte = m_file.readLine();
        if(_arrByte.isEmpty())
        {
            *ppNcCode_ = nullptr;
            return NC_FILE_END;
        }

        int _nRetEqual = _arrByte.indexOf("=", 0);
        int _nRet = _arrByte.indexOf("Refresh", 0);
        if(_nRet != -1 && _nRet < _nRetEqual)
        {
            return GetControl(_arrByte, ppNcCode_);
        }

        _nRet = _arrByte.indexOf("Move", 0);
        if(_nRet != -1 && _nRet < _nRetEqual)
        {
            return GetMove(_arrByte, ppNcCode_);
        }

        _nRet = _arrByte.indexOf("Color", 0);
        if(_nRet != -1 && _nRet < _nRetEqual)
        {
            return GetColor(_arrByte, ppNcCode_);
        }

        _nRet = _arrByte.indexOf("Tip", 0);
        if(_nRet != -1 && _nRet < _nRetEqual)
        {
            return GetTip(_arrByte, ppNcCode_);
        }

        *ppNcCode_ = nullptr;
        return NC_UNEXPECTED_TAG;
    }

    // Refresh={Value=[0/1];}
    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetControl(
            const QByteArray& arrByte_,
            NNcCode::NcCode** ppNcCode_)
    {
        int _nIndex = arrByte_.indexOf("Value", 0);
        if(_nIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        int _nFlag;
        NCFILE_PARSE_RET_CODE _nRet =GetInt(
                arrByte_,
                _nIndex,
                "=",
                "}",
                _nFlag);
        if(_nRet != NC_SUCCESS)
        {
            return NC_UNEXPECTED_VALUE;
        }

        NNcCode::NcCodeControl* _pNcCode = new NNcCode::NcCodeControl();
        _pNcCode->SetEnableRefresh(_nFlag ? true : false);
        *ppNcCode_ = _pNcCode;
        return NC_SUCCESS;
    }

    // Move={\
    // Type=[0/1];\
    // MoveObjs=\
    // {\
    // Name="xxx",\
    // Id=%ld,
    // Pos=xx.xx,\
    // PosWay=[0/1];\
    // ...
    // Name="xxx",\
    // Id=%ld,
    // Pos=xx.xx,\
    // PosWay=[0/1];\
    // \}}
    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetMove(
            const QByteArray& arrByte_,
            NNcCode::NcCode** ppNcCode_)
    {
        NNcCode::NcCodeMove* _pNcCode = new NNcCode::NcCodeMove();
        // Get Type
        int _nIndex = arrByte_.indexOf("Type", 0);
        if(_nIndex != -1)
        {
            int _nType;
            NCFILE_PARSE_RET_CODE _nRet =GetInt(
                    arrByte_,
                    _nIndex++,
                    "=",
                    ";",
                    _nType);
            if(_nRet == NC_SUCCESS
                && (_nType == 0 || _nType == 1))
            {
                _pNcCode->SetMoveType((NNcCode::MOVE_TYPE)_nType);
            }
            else
            {
                delete  _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }
        }

        _nIndex += 6;
        _nIndex = arrByte_.indexOf("MoveObjs", _nIndex);
        if(_nIndex == -1)
        {
            delete  _pNcCode;
            return NC_UNEXPECTED_TAG;
        }

        _nIndex += 9;
        // GetMoveObjs
        while (true)
        {
            _nIndex = arrByte_.indexOf("Name", _nIndex);
            if(_nIndex == -1)
            {
                break;
            }

            // Get MoveObj's Name
            QByteArray _nByteArr;
            NCFILE_PARSE_RET_CODE _nRet = GetString(
                arrByte_,
                _nIndex,
                "\"",
                "\"",
                _nByteArr);

            _nIndex += 7;
            // Get MoveObj's Id
            _nIndex = arrByte_.indexOf("Id", _nIndex);
            if(_nIndex == -1)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_TAG;
            }

            long _nId;
            _nRet = GetLong(
                arrByte_,
                _nIndex,
                "=",
                ",",
                _nId);
            if(_nRet != NC_SUCCESS)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            int _nPos = m_nModalData.FindMoveObj(_nId);
            if(_nPos == -1)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            MoveObj _nMoveObj = m_nModalData.GetMoveObj(_nPos);
            NNcCode::MoveObj _nObj;
            //strncpy(_nObj.m_strObjName, _nByteArr.data(), sizeof(_nObj.m_strObjName));
            _nObj.SetObjectId(_nId);

            _nIndex += 4;
            _nIndex = arrByte_.indexOf("Pos", _nIndex);
            if(_nIndex == -1)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_TAG;
            }

            double _nPosition;
            // Get MoveObj's Pos
            _nRet = GetDouble(
                arrByte_,
                _nIndex,
                "=",
                ",",
                _nPosition);
            if(_nRet != NC_SUCCESS)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            _nIndex += 6;
            _nIndex = arrByte_.indexOf("PosWay", _nIndex);
            if(_nIndex == -1)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_TAG;
            }

            int _nPosWay;
            _nRet =GetInt(
                    arrByte_,
                    _nIndex++,
                    "=",
                    ";",
                    _nPosWay);
            if(_nRet == NC_SUCCESS
                && (_nPosWay == 0 || _nPosWay == 1))
            {
               // do nothing
            }
            else
            {
                delete  _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            // Use Pos And PosWay And CurPos to Set PosDeltaLength
            // 0 Abs
            // 1 Inc
            if(_nPosWay == 0)
            {
                double _nDeltaLength = _nPosition - _nMoveObj.m_nCurPos;
                _nObj.m_nLengthDelta = _nDeltaLength;
                m_nModalData.UpdateMoveObjCurPos(_nPos, _nDeltaLength);
            }

            if(_nPosWay == 1)
            {
                _nObj.m_nLengthDelta = _nPosition;
                m_nModalData.UpdateMoveObjCurPos(_nPos, _nPosition);
            }

            _nIndex += 8;
            _pNcCode->AddMoveObj(_nObj);
        }

        if(_pNcCode->GetMoveObjSize() == 0)
        {
            delete _pNcCode;
            return NC_UNEXPECTED_VALUE;
        }

        *ppNcCode_ = _pNcCode;
        return NC_SUCCESS;
     }

    // Color=\
    // \{
    // Name="xxx",
    // Id=%ld,
    // Value=(R,G,B,A);
    // ...
    // Name="xxx",
    // Id=%ld,
    // Value=(R,G,B,A);
    // \}
    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetColor(
            const QByteArray& arrByte_,
            NNcCode::NcCode** ppNcCode_)
    {
        NNcCode::NcCodeColor* _pNcCode = new NNcCode::NcCodeColor();
        // GetColorObjs
        int _nIndex = 0;
        while (true)
        {
            _nIndex = arrByte_.indexOf("Name", _nIndex);
            if(_nIndex == -1)
            {
                break;
            }

            // Get ColorObj's Name
            QByteArray _nByteArr;
            NCFILE_PARSE_RET_CODE _nRet = GetString(
                arrByte_,
                _nIndex,
                "\"",
                "\"",
                _nByteArr);

            ColorObj _nObj;
            strncpy(_nObj.m_strObjName, _nByteArr.data(), sizeof(_nObj.m_strObjName));

            _nIndex += 7;
            _nIndex = arrByte_.indexOf("Id", _nIndex);
            if(_nIndex == -1)
            {
                break;
            }

            // Get ColorObj's Id
            long _nId;
            _nRet = GetLong(
                arrByte_,
                _nIndex,
                "=",
                ",",
                _nId);

            _nObj.m_nObjectId = _nId;

            _nIndex += 4;
            _nIndex = arrByte_.indexOf("Value", _nIndex);
            if(_nIndex == -1)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_TAG;
            }

            int _nR;
            // Get ColorObj's R
            _nRet = GetInt(
                arrByte_,
                _nIndex,
                "(",
                ",",
                _nR);
            if(_nRet != NC_SUCCESS)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            _nIndex += 6;
            _nIndex = arrByte_.indexOf(",", _nIndex);

            // Get ColorObj's G
            int _nG;
            _nRet = GetInt(
                arrByte_,
                _nIndex,
                ",",
                ",",
                _nG);
            if(_nRet != NC_SUCCESS)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            _nIndex += 2;
            _nIndex = arrByte_.indexOf(",", _nIndex);
            // Get ColorObj's B
            int _nB;
            _nRet = GetInt(
                arrByte_,
                _nIndex,
                ",",
                ",",
                _nB);
            if(_nRet != NC_SUCCESS)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            _nIndex += 2;
            _nIndex = arrByte_.indexOf(",", _nIndex);
            // Get ColorObj's A
            int _nA;
            _nRet = GetInt(
                arrByte_,
                _nIndex,
                ",",
                ")",
                _nA);
            if(_nRet != NC_SUCCESS)
            {
                delete _pNcCode;
                return NC_UNEXPECTED_VALUE;
            }

            _nObj.m_nColor.m_nR = _nR;
            _nObj.m_nColor.m_nG = _nG;
            _nObj.m_nColor.m_nB = _nB;
            _nObj.m_nColor.m_nA = _nA;
            _pNcCode->AddColorObj(_nObj);
            _nIndex += 3;
        }

        if(_pNcCode->GetColorObjSize() == 0)
        {
            delete  _pNcCode;
            return NC_UNEXPECTED_VALUE;
        }

        *ppNcCode_ = _pNcCode;
        return NC_SUCCESS;
    }

    // Tip=
    //{\
    // "xxx"
    //\}
    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetTip(
            const QByteArray& arrByte_,
            NNcCode::NcCode** ppNcCode_)
    {
        NNcCode::NcCodeTip* _pNcCode = new NNcCode::NcCodeTip();
        QByteArray _nArr;
        NCFILE_PARSE_RET_CODE _nRet = GetString(
                    arrByte_,
                    0,
                    "\"",
                    "\"",
                    _nArr);
        if(_nRet != NC_SUCCESS)
        {
            delete _pNcCode;
            return _nRet;
        }

        _pNcCode->SetTip(_nArr);
        *ppNcCode_ = _pNcCode;
        return NC_SUCCESS;
    }

    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetInt(
        const QByteArray& arrByte_,
        int nIndex_,
        const char* strSep1_,
        const char* strSep2_,
        int& nRet_)
    {
        int _nSIndex = arrByte_.indexOf(strSep1_, nIndex_);
        if(_nSIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        _nSIndex++;
        int _nEIndex = arrByte_.indexOf(strSep2_, _nSIndex);
        if(_nEIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        QByteArray _arrTemp = arrByte_.mid(_nSIndex, _nEIndex - _nSIndex);
        bool _bRet;
        long _nValue = _arrTemp.toInt(&_bRet);
        if(!_bRet)
        {
            return NC_UNEXPECTED_VALUE;
        }

        nRet_ = _nValue;
        return NC_SUCCESS;
    }

    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetLong(
        const QByteArray& arrByte_,
        int nIndex_,
        const char* strSep1_,
        const char* strSep2_,
        long& nRet_)
    {
        int _nSIndex = arrByte_.indexOf(strSep1_, nIndex_);
        if(_nSIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        _nSIndex++;
        int _nEIndex = arrByte_.indexOf(strSep2_, _nSIndex);
        if(_nEIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        QByteArray _arrTemp = arrByte_.mid(_nSIndex, _nEIndex - _nSIndex);
        bool _bRet;
        long _nValue = _arrTemp.toLong(&_bRet);
        if(!_bRet)
        {
            return NC_UNEXPECTED_VALUE;
        }

        nRet_ = _nValue;
        return NC_SUCCESS;
    }

    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetDouble(
        const QByteArray& arrByte_,
        int nIndex_,
        const char* strSep1_,
        const char* strSep2_,
        double& nRet_)
    {
        int _nSIndex = arrByte_.indexOf(strSep1_, nIndex_);
        if(_nSIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        _nSIndex++;
        int _nEIndex = arrByte_.indexOf(strSep2_, _nSIndex);
        if(_nEIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        QByteArray _arrTemp = arrByte_.mid(_nSIndex, _nEIndex - _nSIndex);
        bool _bRet;
        long _nValue = _arrTemp.toDouble(&_bRet);
        if(!_bRet)
        {
            return NC_UNEXPECTED_VALUE;
        }

        nRet_ = _nValue;
        return NC_SUCCESS;
    }

    NCFILE_PARSE_RET_CODE ArrayNcFileParse::GetString(
        const QByteArray& arrByte_,
        int nIndex_,
        const char* strSep1_,
        const char* strSep2_,
        QByteArray& nByteArr_)
    {
        int _nSIndex = arrByte_.indexOf(strSep1_, nIndex_);
        if(_nSIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        _nSIndex++;
        int _nEIndex = arrByte_.indexOf(strSep2_, _nSIndex);
        if(_nEIndex == -1)
        {
            return NC_UNEXPECTED_VALUE;
        }

        QByteArray _arrTemp = arrByte_.mid(_nSIndex, _nEIndex - _nSIndex);
        nByteArr_ = _arrTemp;
        return NC_SUCCESS;
    }
}

