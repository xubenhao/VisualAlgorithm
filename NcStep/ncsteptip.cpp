//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "ncsteptip.h"

namespace NNcStep
{
    NcStepTip::NcStepTip(QObject *parent)
        : NcStep(parent)
    {
        memset(m_strTip, 0, sizeof(m_strTip));
        m_nCurTimes = 0;
    }

    void NcStepTip::SetTip(char (&strRet_)[100])
    {
        strncpy(m_strTip, strRet_, sizeof (m_strTip));
    }

    void NcStepTip::SetTip(const QByteArray& nByteArr_)
    {
        strncpy(m_strTip, nByteArr_.data(), sizeof (m_strTip));
    }

    NcStep* NcStepTip::DeepCopy()
    {
        NcStepTip* _pStep = new NcStepTip();
        strncpy(_pStep->m_strTip, m_strTip, sizeof(m_strTip));
        return _pStep;
    }

    void NcStepTip::GetNcShowPrepare()
    {
        m_nCurTimes = 0;
    }

    NNcShow::NcShow* NcStepTip::GetNcShow(
            QWidget* pWidget_,
            NDataStruct::DynArray<NModel::Part*>& arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
            NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_)
    {
        int _nCurTimes = m_nCurTimes++;
        if(_nCurTimes == 0)
        {
            NNcShow::NcShowTip* _pShow = new NNcShow::NcShowTip();
            _pShow->SetTip(m_strTip);
            return _pShow;
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
