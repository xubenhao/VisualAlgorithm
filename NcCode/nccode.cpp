//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "nccode.h"

namespace NNcCode
{
    double NcCode::s_nFixInterpSpeed = 20.0;// mm/s.[logic pos uses mm as unit too]
    double NcCode::s_nFixInterpInterval = 0.02;// 0.02s<--->20ms
    NcCode::NcCode(QObject *parent)
        : QObject(parent)
    {

    }

    void NcCode::GetNcStepPrepare()
    {

    }

    NNcStep::NcStep* NcCode::GetNcStep()
    {
        return nullptr;
    }
}

