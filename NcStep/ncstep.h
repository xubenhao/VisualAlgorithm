//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCSTEP_NCSTEP_H
#define NCSTEP_NCSTEP_H

#include "header.h"

namespace NNcStep
{
    class NcStep : public QObject
    {
        Q_OBJECT
    public:
        explicit NcStep(QObject *parent = nullptr);
        virtual NCSTEP_TYPE GetType(){return NCSTEP_TYPE::_BASE;}
        virtual NcStep* DeepCopy(){return nullptr;}

        virtual void GetNcShowPrepare();
        virtual NNcShow::NcShow* GetNcShow(
                QWidget* pWidget_,
                NDataStruct::DynArray<NModel::Part*>& arrParts_,
                NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
                NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_);

        static int s_nSimuStepLength;
    };
}


#endif // NCSTEP_H
