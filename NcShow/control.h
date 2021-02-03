//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NC_SHOW_CONTROL_H
#define NC_SHOW_CONTROL_H
#include "ncshow.h"

namespace NNcShow
{
    class NcShowControl : public NcShow
    {
    public:
        NcShowControl(QObject *parent = nullptr);
        virtual NCSHOW_TYPE GetType(){return NCSHOW_TYPE::_CONTROL;}
        virtual NcShow* DeepCopy();
        bool GetRefreshEnable(){return m_nRefreshEnable;}
        void SetRefreshEnable(bool bRefreshEnable_){m_nRefreshEnable = bRefreshEnable_;}
    private:
        bool m_nRefreshEnable;
    };
}


#endif // NCSHOWCONTROL_H
