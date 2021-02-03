//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "ncstepcontrol.h"

namespace NNcStep
{
    NcStepControl::NcStepControl(QObject *parent)
        : NcStep(parent)
    {

    }

    NcStep* NcStepControl::DeepCopy()
    {
        NNcStep::NcStepControl* _pControl = new NNcStep::NcStepControl();
        _pControl->m_bEnableRefresh = m_bEnableRefresh;
        _pControl->m_nCurTimes = m_nCurTimes;
        return _pControl;
    }

    void NcStepControl::GetNcShowPrepare()
    {
        m_nCurTimes = 0;
    }

    NNcShow::NcShow* NcStepControl::GetNcShow(
            QWidget* pWidget_,
            NDataStruct::DynArray<NModel::Part*>& arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
            NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_)
    {
        int _nCurTimes = m_nCurTimes++;
        if(_nCurTimes == 0)
        {
            NNcShow::NcShowControl* _pControl = new NNcShow::NcShowControl();
            _pControl->SetRefreshEnable(m_bEnableRefresh);
            return _pControl;
        }
        else if(_nCurTimes == 1)
        {
            return nullptr;
        }
        else
        {
            assert(false);
            return nullptr;
        }
    }
}
