//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCCODE_MOVE_H
#define NCCODE_MOVE_H
#include "nccode.h"

namespace NNcCode
{
    enum MOVE_TYPE
    {
        ONE_JUMP = 0,
        LINEAR_MOVE,
    };

    struct MoveObj
    {
    public:
        MoveObj()
        {
            memset(m_strObjName, 0, sizeof(m_strObjName));
            m_nLengthDelta = 0.0;
            m_nLengthDeltaOnInterval = 0.0;
            m_nObjectId = -1;
        }

        MoveObj(char (&strObjName_)[100], double nLengthDelta_)
        {
            strncpy(m_strObjName, strObjName_, sizeof(m_strObjName));
            m_nLengthDelta = nLengthDelta_;
            m_nLengthDeltaOnInterval = 0.0;
            m_nObjectId = -1;
        }

        long GetObjectId(){return m_nObjectId;}
        void SetObjectId(long nObjectId_){m_nObjectId = nObjectId_;}

        char m_strObjName[100];
        double m_nLengthDelta;
        double m_nLengthDeltaOnInterval;
        long m_nObjectId;
    };

    bool operator==(const MoveObj& nObj1_, const MoveObj& nObj2_);
    bool operator!=(const MoveObj& nObj1_, const MoveObj& nObj2_);

    class NcCodeMove : public NcCode
    {
    public:
        NcCodeMove(QObject *parent = nullptr);
        MoveObj GetMoveObj(int nIndex_)
        {
            if(nIndex_ >= 0 && nIndex_ < m_arrMoveObjs.GetSize())
            {
                return m_arrMoveObjs[nIndex_];
            }

            assert(false);
            return MoveObj();
        }
        int GetMoveObjSize(){return m_arrMoveObjs.GetSize();}
        void AddMoveObj(const MoveObj& nObj_){m_arrMoveObjs.Add(nObj_);}
        void DeleteMoveObj(const MoveObj& nObj_){m_arrMoveObjs.DeleteByValue(nObj_);}
        virtual NCCODE_TYPE GetType(){return NCCODE_TYPE::_MOVE;}
        void SetMoveType(MOVE_TYPE nType_){m_nMoveType = nType_;}
        MOVE_TYPE GetMoveType(){return m_nMoveType;}
        NcCode* DeepCopy();
        virtual void GetNcStepPrepare();
        virtual NNcStep::NcStep* GetNcStep();

    private:
        NDataStruct::DynArray<MoveObj> m_arrMoveObjs;
        MOVE_TYPE m_nMoveType;

        int m_nCurTimes;
        int m_nTotalTimes;
    };
}


#endif // MOVE_H
