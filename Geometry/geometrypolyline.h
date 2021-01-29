//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_POLYLINE_H
#define GEOMETRY_POLYLINE_H
#include "geometry.h"

namespace NGeometry
{
    class GeometryPolyline : public Geometry
    {
        Q_OBJECT
    public:
        GeometryPolyline(QObject* parent = nullptr);
        GeometryPolyline(
                const NStruct::Polyline& nPolyine_, 
                QObject* parent = nullptr);

        virtual ~GeometryPolyline();
        virtual void Draw(
                NTransform::Transform* pTrans_, 
                QPainter& painter);
        virtual void Draw(QPainter& painter);
        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_POLYLINE;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);
    private:
        NStruct::Polyline m_nPolyLine;
    };
}


#endif // POLYLINE_H
