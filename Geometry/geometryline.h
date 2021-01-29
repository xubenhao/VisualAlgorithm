//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_LINE_H
#define GEOMETRY_LINE_H

#include "geometry.h"

namespace NGeometry
{
    class GeometryLine : public Geometry
    {
        Q_OBJECT
    public:
        GeometryLine(QObject* parent = nullptr);
        GeometryLine(
                const NStruct::Line& nLine_, 
                QObject* parent = nullptr);
        virtual ~GeometryLine();
        virtual void Draw(
                NTransform::Transform* pTrans_, 
                QPainter& painter);
        virtual void Draw(QPainter& painter);

        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_LINE;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);

    private:
        NStruct::Line m_nLine;
    };
}


#endif // LINE_H
