//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometryellipse.h"

namespace NGeometry
{
    GeometryEllipse::GeometryEllipse(QObject* parent)
        : Geometry(parent)
    {

    }

    GeometryEllipse::GeometryEllipse(
            const NStruct::Ellipse& nEllipse_, 
            QObject* parent)
        : Geometry(parent)
    {
        m_nEllipse = nEllipse_;
    }

    GeometryEllipse::~GeometryEllipse()
    {
    }

    void GeometryEllipse::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        //NTransform::TRANSFORM_TYPE _nType = pTrans_->GetType();
        // at here,
        // we need print the information of pTrans_ to find error
        pTrans_->PrintDebugInfo();

        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _nTrans(_mxA);
        Geometry* _pGeo = GetTrans(pTrans_);
        _pGeo->Draw(painter);
        delete _pGeo;
    }

    void GeometryEllipse::Draw(QPainter& painter)
    {
        painter.drawEllipse(
                m_nEllipse.GetCenter().toQPointF(), 
                m_nEllipse.GetHRadius(), m_nEllipse.GetVRadius());
    }

    void GeometryEllipse::Trans(NTransform::Transform* pTrans_)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _mxMatrixTrans(_mxA);
        m_nEllipse = _mxMatrixTrans.TransEllipse(m_nEllipse);
    }

    Geometry* GeometryEllipse::GetTrans(
            NTransform::Transform* pTrans_)
    {
        GeometryEllipse* _pGeoPo = new GeometryEllipse(m_nEllipse);
        _pGeoPo->Trans(pTrans_);
        return _pGeoPo;
    }

    Geometry* GeometryEllipse::DeepCopy()
    {
        GeometryEllipse* _pGeo = new GeometryEllipse();
        _pGeo->m_nEllipse = m_nEllipse;
        return _pGeo;
    }

    void GeometryEllipse::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "GeometryEllipse\n Cente.X=%.3f,CenterY=%.3f,HRadius=%.3f,VRadius=%.3f\n",
                    m_nEllipse.GetCenter().GetX(),
                    m_nEllipse.GetCenter().GetY(),
                    m_nEllipse.GetHRadius(),
                    m_nEllipse.GetVRadius());
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}

