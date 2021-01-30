//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef TRANSFORM_ROTATETRANSFORM_H
#define TRANSFORM_ROTATETRANSFORM_H
#include "transform.h"

namespace NTransform
{
    class RotateTransform : public Transform
    {
        Q_OBJECT
    public:
        RotateTransform(QObject* parent = nullptr);
        RotateTransform(
                NStruct::Point poCenter_, 
                double nAngle_, 
                QObject* parent = nullptr);
        virtual NMatrix::Matrix GetMatrix();
        virtual TRANSFORM_TYPE GetType(){return TRANSFORM_MATRIX;}
        virtual Transform* DeepCopy();
        virtual void PrintDebugInfo();
        virtual void PrintDebugInfo(QFile& hFile_);
    private:
        NStruct::Point m_poCenter;
        double m_nAngle;
    };
}


#endif // ROTATETRANSFORM_H
