//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NC_SHOW_NCSHOW_H
#define NC_SHOW_NCSHOW_H

#include "header.h"

namespace NNcShow
{
    class NcShow : public QObject
    {
        Q_OBJECT
    public:
        explicit NcShow(QObject *parent = nullptr);
        virtual NCSHOW_TYPE GetType(){return NCSHOW_TYPE::_BASE;}
        virtual NcShow* DeepCopy(){return nullptr;}
    signals:

    };
}


#endif // NCSHOW_H
