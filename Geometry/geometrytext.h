//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_GEOMETRYTEXT_H
#define GEOMETRY_GEOMETRYTEXT_H
#include "geometry.h"

namespace NGeometry
{
    class GeometryText : public Geometry
    {
    public:
        GeometryText(QObject* parent = nullptr);
        GeometryText(
            const QByteArray& strText_,
            const NStruct::Rect& rcRect_,
            int nFlags_,
            QObject* parent = nullptr);
        virtual ~GeometryText();
        virtual void Draw(
                NTransform::Transform* pTrans_, 
                QPainter& painter);
        virtual void Draw(QPainter& painter);

        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_GEOMETRY;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);

    private:
        QByteArray m_arrByte;
        //NStruct::Point m_poPos;
        NStruct::Rect m_Rect;
        int m_nFlags;
    };
}


#endif // GEOMETRYTEXT_H
