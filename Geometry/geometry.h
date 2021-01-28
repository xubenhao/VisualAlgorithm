//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_GEOMETRY_H
#define GEOMETRY_GEOMETRY_H
#include "header.h"

namespace NGeometry
{
    class GeometryPoint;
    class GeometryLine;
    class GeometryRect;
    class GeometryEllipse;
    class GeometryPolyline;
    class GeometryGroup;
    class Geometry : public QObject
    {
        Q_OBJECT
    public:
        Geometry(QObject* parent = nullptr);
        virtual ~Geometry();
        virtual void Draw(NTransform::Transform* pTrans_, QPainter& painter);
        virtual void Draw(QPainter& painter);

        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_GEOMETRY;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);
    };
}


#endif // GEOMETRY_H
