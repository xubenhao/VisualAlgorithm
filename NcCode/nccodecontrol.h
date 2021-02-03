//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCCODE_CONTROL_H
#define NCCODE_CONTROL_H
#include "nccode.h"

namespace NNcCode
{
    class NcCodeControl : public NcCode
    {
    public:
        NcCodeControl(QObject *parent = nullptr);
        bool GetEnableRefresh(){return m_bEnableRefresh;}
        void SetEnableRefresh(bool bEnableRefresh_){m_bEnableRefresh = bEnableRefresh_;}
        NCCODE_TYPE GetType(){return NCCODE_TYPE::_CONTROL;}
        NcCode* DeepCopy();

        virtual void GetNcStepPrepare();
        virtual NNcStep::NcStep* GetNcStep();
    private:
        bool m_bEnableRefresh;
        int m_nCurTimes;
    };
}

#endif // CONTROL_H
