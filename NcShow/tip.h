//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NC_SHOW_TIP_H
#define NC_SHOW_TIP_H
#include "ncshow.h"

namespace NNcShow
{
    class NcShowTip : public NcShow
    {
    public:
        NcShowTip(QObject *parent = nullptr);
        virtual NCSHOW_TYPE GetType(){return NCSHOW_TYPE::_TIP;}
        virtual NcShow* DeepCopy();
        char* GetTip(){return m_strTip;}
        void SetTip(char (&strRet_)[100]);
        void SetTip(const QByteArray& nByteArr_);
    private:
        char m_strTip[100];
    };
}


#endif // NCSHOWTIP_H
