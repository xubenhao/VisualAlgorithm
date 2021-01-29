//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_RECT_H
#define GEOMETRY_RECT_H
#include "geometry.h"

namespace NGeometry
{
    class GeometryRect : public Geometry
    {
        Q_OBJECT
    public:
        GeometryRect(QObject* parent = nullptr);
        GeometryRect(
                const NStruct::Rect& nRc_, 
                QObject* parent = nullptr);
        virtual ~GeometryRect();
        virtual void Draw(
                NTransform::Transform* pTrans_, 
                QPainter& painter);
        virtual void Draw(QPainter& painter);

        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_RECT;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);
    private:
        NStruct::Rect m_nRect;
    };
}


#endif // RECT_H
