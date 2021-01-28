//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometrypoint.h"

namespace NGeometry
{
    GeometryPoint::GeometryPoint(
            QObject* parent)
        : Geometry(parent)
    {

    }

    GeometryPoint::GeometryPoint(
            const NStruct::Point& poP_, 
            QObject* parent)
        : Geometry(parent)
    {
        m_poPoint = poP_;
    }

    GeometryPoint::~GeometryPoint()
    {

    }

    void GeometryPoint::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _nTrans(_mxA);
        Geometry* _pGeo = GetTrans(pTrans_);
        _pGeo->Draw(painter);
        delete _pGeo;
    }

    void GeometryPoint::Draw(
            QPainter& painter)
    {
        painter.drawPoint(
                QPointF(m_poPoint.GetX(), m_poPoint.GetY()));
    }

    void GeometryPoint::Trans(
            NTransform::Transform* pTrans_)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _mxMatrixTrans(_mxA);
        m_poPoint = _mxMatrixTrans.TransPoint(m_poPoint);
    }

    Geometry* GeometryPoint::GetTrans(
            NTransform::Transform* pTrans_)
    {
        GeometryPoint* _pGeoPo = new GeometryPoint(m_poPoint);
        _pGeoPo->Trans(pTrans_);
        return _pGeoPo;
    }

    Geometry* GeometryPoint::DeepCopy()
    {
        GeometryPoint* _pGeo = new GeometryPoint();
        _pGeo->m_poPoint = m_poPoint;
        return _pGeo;
    }

    void GeometryPoint::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "GeometryLine\n Po.X=%.3f,Po.Y=%.3f\n",
                    m_poPoint.GetX(),
                    m_poPoint.GetY());
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}


