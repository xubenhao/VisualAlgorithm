//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_PARSE_ARRAYNCFILEPARSE_H
#define FILE_PARSE_ARRAYNCFILEPARSE_H

#include "FileParse/fileparse.h"
#include "ncfileparse.h"
namespace NFileParse
{
    struct MoveObj
    {
    public:
        MoveObj()
        {
            memset(m_strObjName, 0, sizeof(m_strObjName));
            m_nCurPos = 0.0;
            m_nObjectId = -1;
        }

        MoveObj(char (&strObjName_)[100], double nPos_)
        {
            strncpy(m_strObjName, strObjName_, sizeof(m_strObjName));
            m_nCurPos = nPos_;
            m_nObjectId = -1;
        }

        char m_strObjName[100];
        double m_nCurPos;
        long m_nObjectId;
    };

    bool operator==(const MoveObj& nObj1_, const MoveObj& nObj2_);
    bool operator!=(const MoveObj& nObj1_, const MoveObj& nObj2_);

    // to do
    // model data should divide two class
    // mutable variable and not-mutable variable
    class ArrayModalData
    {
    public:
        ArrayModalData();
        ~ArrayModalData();
        void AddMoveObj(const MoveObj& nObj_){m_arrMoveObjs.Add(nObj_);}
        void DeleteMoveObj(const MoveObj& nObj_){m_arrMoveObjs.DeleteByValue(nObj_);}
        int FindMoveObj(char* pName_)
        {
            int i = 0;
            for(; i < m_arrMoveObjs.GetSize(); i++)
            {
                if(strcmp(m_arrMoveObjs[i].m_strObjName, pName_) == 0)
                {
                    return i;
                }
            }

            return -1;
        }

        int FindMoveObj(long nId_)
        {
            int i = 0;
            for(; i < m_arrMoveObjs.GetSize(); i++)
            {
                if(m_arrMoveObjs[i].m_nObjectId == nId_)
                {
                    return i;
                }
            }

            return -1;
        }

        MoveObj GetMoveObj(int nIndex_)
        {
            if(nIndex_ < 0 || nIndex_ >= m_arrMoveObjs.GetSize())
            {
                throw "index error";
            }

            return m_arrMoveObjs[nIndex_];
        }

        void UpdateMoveObjCurPos(int nIndex_, double nDelta_)
        {
            if(nIndex_ < 0 || nIndex_ >= m_arrMoveObjs.GetSize())
            {
                throw "index error";
            }

            m_arrMoveObjs[nIndex_].m_nCurPos += nDelta_;
        }
    private:
        NDataStruct::DynArray<MoveObj> m_arrMoveObjs;
    };

    class ArrayNcFileParse : public NcFileParse
    {
    public:
        ArrayNcFileParse(
            const QString& strFilePath_,
            const NParameter::ArrayNcParameter& nParam_,
            const ArrayModalData& nModalData_,
            QObject* pParent_ = nullptr);
        NCFILE_PARSE_RET_CODE GetNcCode(NNcCode::NcCode** ppNcCode_);

    private:
        // 1.NcCode
        // 2.Refresh
        // 3.Index_Pos
        // 4.Index_Color
        // 5.Ret
        NCFILE_PARSE_RET_CODE GetControl(
                const QByteArray& arrByte_,
                NNcCode::NcCode** ppNcCode_);
        NCFILE_PARSE_RET_CODE GetMove(
                const QByteArray& arrByte_,
                NNcCode::NcCode** ppNcCode_);
        NCFILE_PARSE_RET_CODE GetColor(
                const QByteArray& arrByte_,
                NNcCode::NcCode** ppNcCode_);
        NCFILE_PARSE_RET_CODE GetTip(
                const QByteArray& arrByte_,
                NNcCode::NcCode** ppNcCode_);

        NCFILE_PARSE_RET_CODE GetInt(
            const QByteArray& arrByte_,
            int nSIndex_,
            const char* strSep1_,
            const char* strSep2_,
            int& nRet_);
        NCFILE_PARSE_RET_CODE GetLong(
            const QByteArray& arrByte_,
            int nSIndex_,
            const char* strSep1_,
            const char* strSep2_,
            long& nRet_);
        NCFILE_PARSE_RET_CODE GetDouble(
            const QByteArray& arrByte_,
            int nSIndex_,
            const char* strSep1_,
            const char* strSep2_,
            double& nRet_);
        NCFILE_PARSE_RET_CODE GetString(
            const QByteArray& arrByte_,
            int nSIndex_,
            const char* strSep1_,
            const char* strSep2_,
            QByteArray& nStr_);
    protected:
        QFile m_file;
        NParameter::ArrayNcParameter m_nParam;
        NCFILE_PARSE_RET_CODE m_nErrCode;
        ArrayModalData m_nModalData;
    };
}


#endif // ARRAYNCFILEPARSE_H
