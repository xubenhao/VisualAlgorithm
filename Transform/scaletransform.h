//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef TRANSFORM_SCALETRANSFORM_H
#define TRANSFORM_SCALETRANSFORM_H
#include "transform.h"

namespace NTransform
{
    class ScaleTransform : public Transform
    {
        Q_OBJECT
    public:
        ScaleTransform(QObject* parent = nullptr);
        virtual NMatrix::Matrix GetMatrix();
        virtual TRANSFORM_TYPE GetType(){return TRANSFORM_SCALE;}
        virtual Transform* DeepCopy();
        virtual void PrintDebugInfo();
        virtual void PrintDebugInfo(QFile& hFile_);
    private:
        double m_nScaleX;
        double m_nScaleY;
    };
}

#endif // SCALETRANSFORM_H
