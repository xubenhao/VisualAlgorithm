//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef GEOMETRY_GROUP_H
#define GEOMETRY_GROUP_H
#include "geometry.h"

namespace NGeometry
{
    class GeometryGroup : public Geometry
    {
        Q_OBJECT
    public:
        GeometryGroup(
                QObject* parent = nullptr);
        GeometryGroup(
                const NDataStruct::DynArray<Geometry*>& arrGeos_, 
                QObject* parent = nullptr);
        virtual ~GeometryGroup();

        virtual void Draw(
                NTransform::Transform* pTrans_, 
                QPainter& painter);
        virtual void Draw(QPainter& painter);
        virtual void Trans(NTransform::Transform* pTrans_);
        virtual Geometry* GetTrans(NTransform::Transform* pTrans_);
        virtual GEOMETRY_TYPE GetType(){return GEOMETRY_GROUP;}
        virtual Geometry* DeepCopy();
        virtual void OutputDebugInfo(QFile& hFile_);

        void Add(Geometry* pGeo_);
        void Remove(Geometry* pGeo_);
        int GetSize();
    private:
        NDataStruct::DynArray<Geometry*> m_arrGeometrys;
    };
}


#endif // GROUP_H
