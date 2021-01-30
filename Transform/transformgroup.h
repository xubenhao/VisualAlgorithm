//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef TRANSFORM_TRANSFORMGROUP_H
#define TRANSFORM_TRANSFORMGROUP_H
#include "transform.h"

namespace NTransform
{
    class TransformGroup : public Transform
    {
        Q_OBJECT
    public:
        TransformGroup(QObject* parent = nullptr);
        ~TransformGroup();
        virtual TRANSFORM_TYPE GetType(){return TRANSFORM_GROUP;}
        virtual Transform* DeepCopy();

        virtual NMatrix::Matrix GetMatrix();
        void Add(Transform* pTrans_);
        virtual void PrintDebugInfo();
        virtual void PrintDebugInfo(QFile& hFile_);
    private:
        NDataStruct::DynArray<Transform*> m_arrTransforms;
    };
}


#endif // TRANSFORMGROUP_H
