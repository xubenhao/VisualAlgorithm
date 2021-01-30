//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef TRANSFORM_LINEARTRANSFORM_H
#define TRANSFORM_LINEARTRANSFORM_H
#include "transform.h"

namespace NTransform
{
    class LinearTransform : public Transform
    {
        Q_OBJECT
    public:
        LinearTransform(QObject* parent = nullptr);
        LinearTransform(
                double nOffX_, 
                double nOffY_, 
                QObject* parent = nullptr);
        virtual NMatrix::Matrix GetMatrix();
        virtual TRANSFORM_TYPE GetType(){return TRANSFORM_LINEAR;}
        virtual Transform* DeepCopy();
        virtual void PrintDebugInfo();
        virtual void PrintDebugInfo(QFile& hFile_);
    private:
        double m_nOffX;
        double m_nOffY;
    };
}


#endif // LINEARTRANSFORM_H
