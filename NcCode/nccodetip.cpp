//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "nccodetip.h"

namespace NNcCode
{
    NcCodeTip::NcCodeTip(QObject *parent)
        : NcCode(parent)
    {
        memset(m_strTip, 0, sizeof(m_strTip));
        m_nCurTimes = 0;
    }

    void NcCodeTip::SetTip(char (&strTip_)[100])
    {
        strncpy(m_strTip, strTip_, sizeof (m_strTip));
    }

    void NcCodeTip::SetTip(const QByteArray& nByteArr_)
    {
        strncpy(m_strTip, nByteArr_.data(), sizeof (m_strTip));
    }

    NcCode* NcCodeTip::DeepCopy()
    {
        NcCodeTip* _pCode = new NcCodeTip();
        strncpy(_pCode->m_strTip, m_strTip, sizeof(m_strTip));
        return _pCode;
    }

    void NcCodeTip::GetNcStepPrepare()
    {
        m_nCurTimes = 0;
    }

    NNcStep::NcStep* NcCodeTip::GetNcStep()
    {
        int _nCurTimes = m_nCurTimes++;
        if(_nCurTimes == 0)
        {
            NNcStep::NcStepTip* _pStep = new NNcStep::NcStepTip();
            _pStep->SetTip(m_strTip);
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
