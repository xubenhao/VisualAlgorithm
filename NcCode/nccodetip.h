//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCCODE_TIP_H
#define NCCODE_TIP_H
#include "nccode.h"

namespace NNcCode
{
    class NcCodeTip : public NcCode
    {
    public:
        NcCodeTip(QObject *parent = nullptr);

        char* GetTip(){return m_strTip;}
        void SetTip(char (&strTip_)[100]);
        void SetTip(const QByteArray& nByteArr_);
        virtual NCCODE_TYPE GetType(){return NCCODE_TYPE::_TIP;}
        NcCode* DeepCopy();
        virtual void GetNcStepPrepare();
        virtual NNcStep::NcStep* GetNcStep();
    private:
        char m_strTip[100];
        int m_nCurTimes;
    };
}

#endif // TIP_H
