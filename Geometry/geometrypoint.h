//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H
#include "geometry.h"

class QPainter;
namespace NTransform
{
    class Transform;
}

namespace NGeometry
{
    class Geometry;

    class GeometryPoint : public Geometry
    {
        Q_OBJECT
    public:
        GeometryPoint(QObject* parent = nullptr);
        GeometryPoint(
                const NStruct::Point& poP_, 
                QObject* parent = nullptr);
        virtual ~GeometryPoint();
        virtual void Draw(
                NTransform::Transform* pTrans_, 
                QPainter& painter);
        virtual void Draw(QPainter& painter);

        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_POINT;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);

    private:
        NStruct::Point m_poPoint;
    };
}

#endif // POINT_H
