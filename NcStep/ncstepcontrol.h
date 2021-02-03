//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCSTEP_CONTROL_H
#define NCSTEP_CONTROL_H
#include "ncstep.h"
namespace NNcStep
{
    class NcStepControl : public NcStep
    {
    public:
        NcStepControl(QObject *parent = nullptr);
        bool GetEnableRefresh(){return m_bEnableRefresh;}
        void SetEnableRefresh(bool bEnableRefresh_){m_bEnableRefresh = bEnableRefresh_;}
        virtual NCSTEP_TYPE GetType(){return NCSTEP_TYPE::_CONTROL;}
        virtual NcStep* DeepCopy();

        virtual void GetNcShowPrepare();
        virtual NNcShow::NcShow* GetNcShow(
                QWidget* pWidget_,
                NDataStruct::DynArray<NModel::Part*>& arrParts_,
                NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
                NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_);
    private:
        bool m_bEnableRefresh;
        int m_nCurTimes;
    };
}



#endif // CONTROL_H
