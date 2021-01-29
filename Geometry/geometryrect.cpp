//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometryrect.h"

namespace NGeometry
{
    GeometryRect::GeometryRect(QObject* parent)
        : Geometry(parent)
    {
    }

    GeometryRect::GeometryRect(
            const NStruct::Rect& nRc_, 
            QObject* parent)
        : Geometry(parent)
    {
        m_nRect = nRc_;
    }

    GeometryRect::~GeometryRect()
    {

    }

    // a designe mode
    // base class definate a standard process steps
    // drivered class can define itself's version for every step
    void GeometryRect::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _nTrans(_mxA);
        Geometry* _pGeo = GetTrans(pTrans_);
        _pGeo->Draw(painter);
        delete _pGeo;
    }

    void GeometryRect::Draw(QPainter& painter)
    {
        NStruct::Polyline _nPoyline = m_nRect.ToPolyLine();
        QPointF _arrPos[4];
        int _nSize = _nPoyline.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            _arrPos[i] = _nPoyline.Get(i).toQPointF();
        }

        painter.drawPolygon(_arrPos, 4);
    }

    void GeometryRect::Trans(NTransform::Transform* pTrans_)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _mxMatrixTrans(_mxA);
        m_nRect = _mxMatrixTrans.TransRect(m_nRect);
    }

    Geometry* GeometryRect::GetTrans(NTransform::Transform* pTrans_)
    {
        GeometryRect* _pGeoPo = new GeometryRect(m_nRect);
        _pGeoPo->Trans(pTrans_);
        return _pGeoPo;
    }

    Geometry* GeometryRect::DeepCopy()
    {
        GeometryRect* _pGeo = new GeometryRect();
        _pGeo->m_nRect = m_nRect;
        return _pGeo;
    }

    void GeometryRect::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "Rect:\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
        _str = QString::asprintf(
            "LeftUp.X=%.3f,LeftUp.Y=%.3f,Width=%.3f,Height=%.3f,Angle=%.3f\n",
            m_nRect.GetLeftUp().GetX(),
            m_nRect.GetLeftUp().GetY(),
            m_nRect.GetWeight(),
            m_nRect.GetHeight(),
            m_nRect.GetCalcAngle());
        _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}

