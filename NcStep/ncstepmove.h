//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCSTEP_MOVE_H
#define NCSTEP_MOVE_H
#include "ncstep.h"

namespace NNcStep
{
    struct MoveObj
    {
    public:
        MoveObj()
        {
            memset(m_strObjName, 0, sizeof(m_strObjName));
            m_nLengthDelta = 0.0;
            m_nObjectId = -1;
        }

        MoveObj(
            char (&strObjName_)[100],
            double nLengthDelta_,
            long nObjectId_)
        {
            strncpy(m_strObjName, strObjName_, sizeof(m_strObjName));
            m_nLengthDelta = nLengthDelta_;
            m_nObjectId = nObjectId_;
        }

        long GetObjectId(){return m_nObjectId;}
        void SetObjectId(long nObjectId_){m_nObjectId = nObjectId_;}

        char m_strObjName[100];
        double m_nLengthDelta;
        long m_nObjectId;
    };

    bool operator==(const MoveObj& nObj1_, const MoveObj& nObj2_);
    bool operator!=(const MoveObj& nObj1_, const MoveObj& nObj2_);

    class NcStepMove : public NcStep
    {
    public:
        NcStepMove(QObject *parent = nullptr);

        int GetMoveObjSize()
        {
            return m_arrMoveObjs.GetSize();
        }

        MoveObj GetMoveObj(int nIndex_)
        {
            if(nIndex_ >= 0 && nIndex_ < m_arrMoveObjs.GetSize())
            {
                return m_arrMoveObjs[nIndex_];
            }

            assert(false);
            return MoveObj();
        }
        void AddMoveObj(const MoveObj& nObj_){m_arrMoveObjs.Add(nObj_);}
        void DeleteMoveObj(const MoveObj& nObj_){m_arrMoveObjs.DeleteByValue(nObj_);}
        virtual NCSTEP_TYPE GetType(){return NCSTEP_TYPE::_MOVE;}
        virtual NcStep* DeepCopy();
        virtual void GetNcShowPrepare();
        virtual NNcShow::NcShow* GetNcShow(
                QWidget* pWidget_,
                NDataStruct::DynArray<NModel::Part*>& arrParts_,
                NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
                NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_);

    private:
        NDataStruct::DynArray<MoveObj> m_arrMoveObjs;

        // For Interp
        int m_nCurTimes;
    };


}

#endif // MOVE_H
