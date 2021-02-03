//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "nccodecolor.h"

namespace NNcCode
{
    NcCodeColor::NcCodeColor(QObject *parent)
        : NcCode(parent)
    {
        m_nCurTimes = 0;
    }

    NcCode* NcCodeColor::DeepCopy()
    {
        NcCodeColor* _pCode = new NcCodeColor();
        _pCode->m_arrColorObjs = m_arrColorObjs;
        return _pCode;
    }

    void NcCodeColor::GetNcStepPrepare()
    {
        m_nCurTimes = 0;
    }

    NNcStep::NcStep* NcCodeColor::GetNcStep()
    {
        int _nCurTimes = m_nCurTimes++;
        if(_nCurTimes == 0)
        {
            NNcStep::NcStepColor* _pStep = new NNcStep::NcStepColor();
            for(int i = 0; i < m_arrColorObjs.GetSize(); i++)
            {
                _pStep->AddColorObj(m_arrColorObjs[i]);
            }

            return _pStep;
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
