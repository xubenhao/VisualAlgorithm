//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayncfilegenerate.h"

namespace NFileGenerate
{
    ArrayNcFileGenerate::ArrayNcFileGenerate(QObject* object)
        : NcFileGenerate(object)
    {

    }

    int ArrayNcFileGenerate::GenerateForSearch(
            const QString& filePath_,
            char* pContent_)
    {
        m_file.close();
        m_file.setFileName(filePath_);
        bool _bRet = m_file.open(
                    QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        if(!_bRet)
        {
            return ACCESS_ERROR;
        }

        // how to generate search file
        int _nSize = m_nParam.m_nSize;
        QString _str;
        QByteArray _nByteArr;
        int i = 0;
        double _nPos = 0.0;
        char _strInfo[100];
        for(; i < _nSize; i++)
        {
            if(i != 0.0)
            {
                _nPos += (m_nParam.m_arrElements[i-1].m_nSize.m_nWidth/2.0
                        +m_nParam.m_arrElements[i].m_nSize.m_nWidth/2.0);
            }

            _str = QString::asprintf("Move={ Type=1; MoveObjs={ Name=\"%s\", Id=%ld, Pos=%.f,PosWay=0; } }\n",
                m_nParam.m_strScaleName,
                m_nParam.m_nScaleId,
                _nPos);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
            char* _pStr = m_nParam.m_arrElements[i].m_strContent;
            memset(_strInfo, 0, sizeof(_strInfo));
            sprintf(_strInfo, "索引%d位置元素与%s进行比较",
                    i, pContent_);
            _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                _strInfo);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
            if(strcmp(pContent_, _pStr) == 0)
            {
                memset(_strInfo, 0, sizeof(_strInfo));
                sprintf(_strInfo, "索引%d位置元素与%s匹配",
                        i, pContent_);
                _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                    _strInfo);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();

                QColor _nCol = NParameter::GetColor(m_nParam.m_arrElements[i].m_nMatch);
                int _nR, _nG, _nB, _nA;
                _nCol.getRgb(&_nR, &_nG, &_nB, &_nA);

                _str = QString::asprintf("Color={ Name=\"%s\", Id=%ld, Value=(%d,%d,%d,%d);}\n",
                    m_nParam.m_arrElements[i].m_strName,
                    m_nParam.m_arrElements[i].m_nObjectId,
                    _nR, _nG, _nB, _nA);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();
                break;
            }
            else
            {
                memset(_strInfo, 0, sizeof(_strInfo));
                sprintf(_strInfo, "索引%d位置元素与%s不匹配",
                        i, pContent_);
                _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                    _strInfo);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();

                QColor _nCol = NParameter::GetColor(m_nParam.m_arrElements[i].m_nNotMatch);
                int _nR, _nG, _nB, _nA;
                _nCol.getRgb(&_nR, &_nG, &_nB, &_nA);

                _str = QString::asprintf("Color={ Name=\"%s\", Id=%ld, Value=(%d,%d,%d,%d);}\n",
                    m_nParam.m_arrElements[i].m_strName,
                    m_nParam.m_arrElements[i].m_nObjectId,
                    _nR, _nG, _nB, _nA);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();
            }
        }

        if(i < _nSize)
        {
            char _strInfo[100];
            memset(_strInfo, 0, sizeof(_strInfo));
            sprintf(_strInfo, "在索引%d位置找到查找元素", i);
            _str = QString::asprintf("Tip={ Value=\"%s\"; }",
                _strInfo);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
        }
        else
        {
            _str = QString::asprintf("Tip ={ Value=\"查找元素在数组内不存在\"; };\n");
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
        }

        m_file.flush();
        m_file.close();
        return SUCCESS;
    }

    int ArrayNcFileGenerate::GenerateForDelete(
            const QString& filePath_,
            int nIndex_,
            double nDeltaLength_)
    {
        m_file.close();
        m_file.setFileName(filePath_);
        bool _bRet = m_file.open(
                    QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        if(!_bRet)
        {
            return ACCESS_ERROR;
        }

        // how to generate delete file
        int _nSize = m_nParam.m_nSize;
        QString _str;
        QByteArray _nByteArr;
        int i = 0;
        double _nPos = 0.0;
        char _strInfo[100];

        if(nIndex_ < 0 || nIndex_ >= _nSize)
        {
            memset(_strInfo, 0, sizeof(_strInfo));
            sprintf(_strInfo, "The delete index position is not legal");
            _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                _strInfo);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
            return SUCCESS;
        }

        {
            memset(_strInfo, 0, sizeof(_strInfo));
            sprintf(_strInfo, "将删除元素移出数组");
            _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                _strInfo);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();

            // PosWay:
            // 0 Abs
            // 1 Inc
            _str = QString::asprintf("Move={ Type=1; MoveObjs={ Name=\"%s\", Id=%ld, Pos=%.f,PosWay=1; } }\n",
                m_nParam.m_arrElements[nIndex_].m_strName,
                m_nParam.m_arrElements[nIndex_].m_nObjectId,
                nDeltaLength_);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();

            for(int i = nIndex_+1; i < _nSize; i++)
            {
                _nPos = (m_nParam.m_arrElements[i].m_nSize.m_nWidth/2.0
                        +m_nParam.m_arrElements[i-1].m_nSize.m_nWidth/2.0);
                m_nParam.m_arrElements[i-1] = m_nParam.m_arrElements[i];
                memset(_strInfo, 0, sizeof(_strInfo));
                sprintf(_strInfo, "移动索引%d位置元素到其前一位置",
                        i);
                _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                    _strInfo);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();

                // PosWay:
                // 0 Abs
                // 1 Inc
                _str = QString::asprintf("Move={ Type=1; MoveObjs={ Name=\"%s\", Id=%ld, Pos=%.f,PosWay=1; } }\n",
                    m_nParam.m_arrElements[i].m_strName,
                    m_nParam.m_arrElements[i].m_nObjectId,
                    -_nPos);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();
            }
        }


        memset(_strInfo, 0, sizeof(_strInfo));
        sprintf(_strInfo, "Finish",
                i);
        _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
            _strInfo);
        _nByteArr = _str.toUtf8();
        m_file.write(_nByteArr);
        m_file.flush();

        m_file.close();
        return SUCCESS;
    }

    int ArrayNcFileGenerate::GenerateForInsert(
            const QString& filePath_,
            char* pContent_,
            int nIndex_,
            double nDeltaLength_,
            long nInsertObjId_)
    {
        m_file.close();
        m_file.setFileName(filePath_);
        bool _bRet = m_file.open(
                    QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        if(!_bRet)
        {
            return ACCESS_ERROR;
        }

        // how to generate search file
        int _nSize = m_nParam.m_nSize;
        QString _str;
        QByteArray _nByteArr;
        //int i = 0;
        double _nPos = 0.0;
        char _strInfo[100];

        if(_nSize == m_nParam.m_nCapacity)
        {
            memset(_strInfo, 0, sizeof(_strInfo));
            sprintf(_strInfo, "数组已满，无法插入");
            _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                _strInfo);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
            return SUCCESS;
        }

        if(nIndex_ < 0 || nIndex_ > _nSize)
        {
            memset(_strInfo, 0, sizeof(_strInfo));
            sprintf(_strInfo, "插入位置%d不是合法位置",
                    nIndex_);
            _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                _strInfo);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
        }
        else
        {
            m_nParam.m_arrElements.Add(NParameter::ArrayNcElement());
            for(int i = _nSize - 1; i >= nIndex_; i--)
            {

                _nPos = (m_nParam.m_arrElements[i].m_nSize.m_nWidth/2.0
                        +m_nParam.m_arrElements[i+1].m_nSize.m_nWidth/2.0);
                m_nParam.m_arrElements[i+1] = m_nParam.m_arrElements[i];
                memset(_strInfo, 0, sizeof(_strInfo));
                sprintf(_strInfo, "移动索引%d位置元素到下一位置",
                        i);
                _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                    _strInfo);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();

                // PosWay:
                // 0 Abs
                // 1 Inc
                _str = QString::asprintf("Move={ Type=1; MoveObjs={ Name=\"%s\", Id=%ld, Pos=%.f,PosWay=1; } }\n",
                    m_nParam.m_arrElements[i].m_strName,
                    m_nParam.m_arrElements[i].m_nObjectId,
                    _nPos);
                _nByteArr = _str.toUtf8();
                m_file.write(_nByteArr);
                m_file.flush();
            }

            NParameter::ArrayNcElement _nEle;
            _nEle.m_nSize = m_nParam.m_arrElements[0].m_nSize;
            _nEle.m_nDefault = m_nParam.m_arrElements[0].m_nDefault;
            _nEle.m_nMatch = m_nParam.m_arrElements[0].m_nMatch;
            _nEle.m_nNotMatch = m_nParam.m_arrElements[0].m_nNotMatch;
            strncpy(
                _nEle.m_strContent,
                pContent_,
                sizeof(_nEle.m_strContent));
            strncpy(
                _nEle.m_strName,
                pContent_,
                sizeof(_nEle.m_strName));
            _nEle.m_nObjectId = nInsertObjId_;
            m_nParam.m_arrElements[nIndex_] = _nEle;

            //_nPos = ();
            //m_nParam.m_arrElements[i+1] = m_nParam.m_arrElements[i];
            memset(_strInfo, 0, sizeof(_strInfo));
            sprintf(_strInfo, "移动插入元素到索引%d位置",
                    nIndex_);
            _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
                _strInfo);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();

            // PosWay:
            // 0 Abs
            // 1 Inc
            _str = QString::asprintf("Move={ Type=1; MoveObjs={ Name=\"%s\", Id=%ld, Pos=%.f,PosWay=1; } }\n",
                m_nParam.m_arrElements[nIndex_].m_strName,
                m_nParam.m_arrElements[nIndex_].m_nObjectId,
                nDeltaLength_);
            _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
            m_file.flush();
        }


        memset(_strInfo, 0, sizeof(_strInfo));
        sprintf(_strInfo, "Finish");
        _str = QString::asprintf("Tip={ Value=\"%s\"; }\n",
            _strInfo);
        _nByteArr = _str.toUtf8();
        m_file.write(_nByteArr);
        m_file.flush();
        m_file.close();
        return SUCCESS;
    }



}
