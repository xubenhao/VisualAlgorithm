//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef TRANSFORM_MATRIXTRANSFORM_H
#define TRANSFORM_MATRIXTRANSFORM_H
#include "transform.h"

namespace NTransform
{
    class MatrixTransform : public Transform
    {
        Q_OBJECT
    public:
        MatrixTransform(QObject* parent = nullptr);
        MatrixTransform(
                const NMatrix::Matrix& mxA_, 
                QObject* parent = nullptr);
        virtual NMatrix::Matrix GetMatrix();
        virtual TRANSFORM_TYPE GetType(){return TRANSFORM_MATRIX;}
        virtual Transform* DeepCopy();

        NStruct::Point TransPoint(const NStruct::Point& poP_);
        NStruct::Line TransLine(const NStruct::Line& nLine_);
        NStruct::Rect TransRect(const NStruct::Rect& nRect_);
        NStruct::Ellipse TransEllipse(
                const NStruct::Ellipse& nCircle_);
        NStruct::Polyline TransPolyline(
                const NStruct::Polyline& nPolyline_);
        virtual void PrintDebugInfo();
        virtual void PrintDebugInfo(QFile& hFile_);
        /*Group TransGroup(const Group& nGroup_);*/
    private:
        NMatrix::Matrix m_mxM;
    };
}


#endif // MATRIXTRANSFORM_H
