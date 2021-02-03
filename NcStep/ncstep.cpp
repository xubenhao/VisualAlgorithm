//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "ncstep.h"

namespace NNcStep
{
    int NcStep::s_nSimuStepLength = 6;
    NcStep::NcStep(QObject *parent) : QObject(parent)
    {

    }

    void NcStep::GetNcShowPrepare()
    {

    }

    NNcShow::NcShow* NcStep::GetNcShow(
            QWidget* pWidget_,
            NDataStruct::DynArray<NModel::Part*>& arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
            NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_)
    {
        return nullptr;
    }
}

