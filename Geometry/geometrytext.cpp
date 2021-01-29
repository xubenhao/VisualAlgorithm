//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometrytext.h"

namespace NGeometry
{
    GeometryText::GeometryText(QObject* parent)
        : Geometry(parent)
    {

    }

    GeometryText::GeometryText(
        const QByteArray& strText_,
        const NStruct::Rect& rcRect_,
        int nFlags_,
        QObject* parent)
        : Geometry(parent)
    {
        m_arrByte = strText_;
        //m_poPos = poP_;
        m_Rect = rcRect_;
        m_nFlags = nFlags_;
    }

    GeometryText::~GeometryText()
    {

    }

    void GeometryText::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _nTrans(_mxA);
        Geometry* _pGeo = GetTrans(pTrans_);
        _pGeo->Draw(painter);
        delete _pGeo;
    }

    void GeometryText::Draw(QPainter& painter)
    {
        //painter.drawText(
        //  QPointF(m_poPos.GetX(), m_poPos.GetY()), m_arrByte);
        painter.drawText(m_Rect.ToQRectF(), m_nFlags, m_arrByte);
    }

    void GeometryText::Trans(NTransform::Transform* pTrans_)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _mxMatrixTrans(_mxA);
        //m_poPos = _mxMatrixTrans.TransPoint(m_poPos);
        m_Rect = _mxMatrixTrans.TransRect(m_Rect);
    }

    Geometry* GeometryText::GetTrans(
            NTransform::Transform* pTrans_)
    {
        GeometryText* _pGeo 
            = new GeometryText(m_arrByte, m_Rect, m_nFlags);
        _pGeo->Trans(pTrans_);
        return _pGeo;
    }

    Geometry* GeometryText::DeepCopy()
    {
        GeometryText* _pGeo = new GeometryText();
        _pGeo->m_arrByte = m_arrByte;
        //_pGeo->m_poPos = m_poPos;
        _pGeo->m_Rect = m_Rect;
        _pGeo->m_nFlags = m_nFlags;
        return _pGeo;
    }

    void GeometryText::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "GeometryText\n %s\n",
                    m_arrByte.data());
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}

