//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometrypolyline.h"

namespace NGeometry
{
    GeometryPolyline::GeometryPolyline(QObject* parent)
        : Geometry(parent)
    {

    }

    GeometryPolyline::GeometryPolyline(
            const NStruct::Polyline& nPolyine_, 
            QObject* parent)
        : Geometry(parent)
    {
        m_nPolyLine = nPolyine_;
    }

    GeometryPolyline::~GeometryPolyline()
    {

    }

    void GeometryPolyline::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _nTrans(_mxA);
        Geometry* _pGeo = GetTrans(pTrans_);
        _pGeo->Draw(painter);
        delete _pGeo;
    }

    void GeometryPolyline::Draw(QPainter& painter)
    {
        int _nSize = m_nPolyLine.GetSize();
        QPointF _arrPos[_nSize];
        for(int i = 0; i < _nSize; i++)
        {
            _arrPos[i] = m_nPolyLine.Get(i).toQPointF();
        }

        painter.drawPolyline(_arrPos, _nSize);
    }

    void GeometryPolyline::Trans(
            NTransform::Transform* pTrans_)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _mxMatrixTrans(_mxA);
        m_nPolyLine = _mxMatrixTrans.TransPolyline(m_nPolyLine);
    }

    Geometry* GeometryPolyline::GetTrans(
            NTransform::Transform* pTrans_)
    {
        GeometryPolyline* _pGeoPo = new GeometryPolyline(m_nPolyLine);
        _pGeoPo->Trans(pTrans_);
        return _pGeoPo;
    }

    Geometry* GeometryPolyline::DeepCopy()
    {
        GeometryPolyline* _pGeo = new GeometryPolyline();
        _pGeo->m_nPolyLine = m_nPolyLine;
        return _pGeo;
    }

    void GeometryPolyline::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "GeometryPolyline\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
        for(int i = 0; i < m_nPolyLine.GetSize(); i++)
        {
            NStruct::Point _poPoint = m_nPolyLine.Get(i);
            _str = QString::asprintf("Point:X=%.3f,Y=%.3f\n",
                                     _poPoint.GetX(),
                                     _poPoint.GetY());
            _nByteArr = _str.toUtf8();
            hFile_.write(_nByteArr);
            hFile_.flush();
        }
    }
}

