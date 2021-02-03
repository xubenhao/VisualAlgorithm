//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCSTEP_TIP_H
#define NCSTEP_TIP_H

#include "ncstep.h"
namespace NNcStep
{
    class NcStepTip : public NcStep
    {
    public:
        NcStepTip(QObject* object = nullptr);
        char* GetTip(){return m_strTip;}
        void SetTip(char (&strRet_)[100]);
        void SetTip(const QByteArray& nByteArr_);
        virtual NCSTEP_TYPE GetType(){return NCSTEP_TYPE::_TIP;}
        virtual NcStep* DeepCopy();
        void GetNcShowPrepare();
        virtual NNcShow::NcShow* GetNcShow(
                QWidget* pWidget_,
                NDataStruct::DynArray<NModel::Part*>& arrParts_,
                NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
                NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_);
    private:
        char m_strTip[100];
        int m_nCurTimes;
    };
}

#endif // TIP_H
