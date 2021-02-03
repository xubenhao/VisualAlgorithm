//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCCODE_NCCODE_H
#define NCCODE_NCCODE_H
#include "header.h"

namespace NNcCode
{
    class NcCode : public QObject
    {
        Q_OBJECT
    public:
        explicit NcCode(QObject *parent = nullptr);
        virtual NCCODE_TYPE GetType(){return NCCODE_TYPE::_BASE;}
        NcCode* DeepCopy(){return nullptr;}
        virtual void GetNcStepPrepare();
        virtual NNcStep::NcStep* GetNcStep();
    protected:
        static double s_nFixInterpSpeed;
        static double s_nFixInterpInterval;
    };
}


#endif // NCCODE_H
