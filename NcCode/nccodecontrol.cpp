//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "nccodecontrol.h"
namespace NNcCode
{
    NcCodeControl::NcCodeControl(QObject *parent)
        : NcCode(parent)
    {

    }

    NcCode* NcCodeControl::DeepCopy()
    {
        NcCodeControl* _pControl = new NcCodeControl();
        _pControl->m_bEnableRefresh = m_bEnableRefresh;
        _pControl->m_nCurTimes = m_nCurTimes;
        return _pControl;
    }

    void NcCodeControl::GetNcStepPrepare()
    {
        m_nCurTimes = 0;
    }

    NNcStep::NcStep* NcCodeControl::GetNcStep()
    {
        int _nCurTimes = m_nCurTimes++;
        if(_nCurTimes == 0)
        {
            NNcStep::NcStepControl* _pControl = new NNcStep::NcStepControl();
            _pControl->SetEnableRefresh(m_bEnableRefresh);
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
