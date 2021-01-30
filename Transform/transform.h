//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef TRANSFORM_TRANSFORM_H
#define TRANSFORM_TRANSFORM_H
#include "header.h"

namespace NTransform
{
    class Transform : public QObject
    {
        Q_OBJECT
    public:
        Transform(QObject* parent = nullptr);
        virtual ~Transform();
        virtual NMatrix::Matrix GetMatrix();
        virtual TRANSFORM_TYPE GetType(){return TRANSFORM_TRANSFORM;}
        virtual Transform* DeepCopy();
        virtual void PrintDebugInfo();
        virtual void PrintDebugInfo(QFile& hFile_);
    };
}

#endif // TRANSFORM_H
