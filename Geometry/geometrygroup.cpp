//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometrygroup.h"

namespace NGeometry
{
    GeometryGroup::GeometryGroup(QObject* parent)
        : Geometry(parent)
    {

    }

    GeometryGroup::GeometryGroup(
            const NDataStruct::DynArray<Geometry*>& arrGeos_, 
            QObject* parent)
        : Geometry(parent)
    {
        m_arrGeometrys = arrGeos_;
    }

    GeometryGroup::~GeometryGroup()
    {

    }

    void GeometryGroup::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        int _nSize = m_arrGeometrys.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            m_arrGeometrys[i]->Draw(pTrans_, painter);
        }
    }

    void GeometryGroup::Draw(QPainter& painter)
    {
        int _nSize = m_arrGeometrys.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            m_arrGeometrys[i]->Draw(painter);
        }
    }

    void GeometryGroup::Trans(NTransform::Transform* pTrans_)
    {
        NDataStruct::DynArray<Geometry*> _arrGeos;
        int _nSize = m_arrGeometrys.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            _arrGeos.Add(m_arrGeometrys[i]->GetTrans(pTrans_));
        }

        this->~GeometryGroup();
        m_arrGeometrys = _arrGeos;
        for(int i = 0; i < _nSize; i++)
        {
            m_arrGeometrys[i]->setParent(this);
        }
    }

    Geometry* GeometryGroup::GetTrans(
            NTransform::Transform* pTrans_)
    {
        NDataStruct::DynArray<Geometry*> _arrGeos;
        int _nSize = m_arrGeometrys.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            _arrGeos.Add(m_arrGeometrys[i]->GetTrans(pTrans_));
        }

        GeometryGroup* _pGeoGroup = new GeometryGroup(_arrGeos);
        for(int i = 0; i < _nSize; i++)
        {
            _arrGeos[i]->setParent(_pGeoGroup);
        }

        return _pGeoGroup;
    }

    Geometry* GeometryGroup::DeepCopy()
    {
        GeometryGroup* _pGeoGroup = new GeometryGroup();
        int _nSize = m_arrGeometrys.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            Geometry* _pGeo = m_arrGeometrys[i]->DeepCopy();
            _pGeoGroup->Add(_pGeo);
            _pGeo->setParent(_pGeoGroup);
        }

        return _pGeoGroup;
    }

    void GeometryGroup::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "This is geometry-group\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();

        for(int i = 0; i < m_arrGeometrys.GetSize(); i++)
        {
            m_arrGeometrys[i]->OutputDebugInfo(hFile_);
        }
    }

    void GeometryGroup::Add(Geometry* pGeo_)
    {
        m_arrGeometrys.Add(pGeo_);
    }

    void GeometryGroup::Remove(Geometry* pGeo_)
    {
        m_arrGeometrys.DeleteByValue(pGeo_);
    }

    int GeometryGroup::GetSize()
    {
        return m_arrGeometrys.GetSize();
    }
}


