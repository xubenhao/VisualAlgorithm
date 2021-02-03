//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "tip.h"

namespace NNcShow
{
    NcShowTip::NcShowTip(QObject *parent)
        : NcShow(parent)
    {
        memset(m_strTip, 0, sizeof(m_strTip));
    }

    NcShow* NcShowTip::DeepCopy()
    {
        NNcShow::NcShowTip* _pShow = new NNcShow::NcShowTip();
        _pShow->SetTip(m_strTip);
        return _pShow;
    }

    void NcShowTip::SetTip(char (&strRet_)[100])
    {
        strncpy(m_strTip, strRet_, sizeof(m_strTip));
    }

    void NcShowTip::SetTip(const QByteArray& nByteArr_)
    {
        strncpy(m_strTip, nByteArr_.data(), sizeof (m_strTip));
    }
}
