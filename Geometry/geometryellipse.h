//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_CIRCLE_H
#define GEOMETRY_CIRCLE_H
#include "geometry.h"

namespace NGeometry
{
    class GeometryEllipse : public Geometry
    {
        Q_OBJECT
    public:
        GeometryEllipse(QObject* parent = nullptr);
        GeometryEllipse(
                const NStruct::Ellipse& nEllipse_, 
                QObject* parent = nullptr);
        virtual ~GeometryEllipse();

        virtual void Draw(
                NTransform::Transform* pTrans_, 
                QPainter& painter);
        virtual void Draw(QPainter& painter);
        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_ELLIPSE;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);

    private:
        NStruct::Ellipse m_nEllipse;
    };
}


#endif // CIRCLE_H
