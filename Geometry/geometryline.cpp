//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometryline.h"

namespace NGeometry
{
    GeometryLine::GeometryLine(QObject* parent)
        : Geometry(parent)
    {

    }

    GeometryLine::GeometryLine(
            const NStruct::Line& nLine_, 
            QObject* parent)
        : Geometry(parent)
    {
        m_nLine = nLine_;
    }

    GeometryLine::~GeometryLine()
    {

    }

    void GeometryLine::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _nTrans(_mxA);
        Geometry* _pGeo = GetTrans(pTrans_);
        _pGeo->Draw(painter);
        delete _pGeo;
    }

    void GeometryLine::Draw(QPainter& painter)
    {
        painter.drawLine(
                m_nLine.GetStart().toQPointF(), 
                m_nLine.GetEnd().toQPointF());
    }

    void GeometryLine::Trans(NTransform::Transform* pTrans_)
    {
        NMatrix::Matrix _mxA = pTrans_->GetMatrix();
        NTransform::MatrixTransform _mxMatrixTrans(_mxA);
        m_nLine = _mxMatrixTrans.TransLine(m_nLine);
    }

    Geometry* GeometryLine::GetTrans(NTransform::Transform* pTrans_)
    {
        GeometryLine* _pGeoPo = new GeometryLine(m_nLine);
        _pGeoPo->Trans(pTrans_);
        return _pGeoPo;
    }

    Geometry* GeometryLine::DeepCopy()
    {
       GeometryLine* _pGeo = new GeometryLine();
       _pGeo->m_nLine = m_nLine;
       return _pGeo;
    }

    void GeometryLine::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "GeometryLine\n PoS.X=%.3f,PoS.Y=%.3f,PoE.X=%.3f,PoE.Y=%.3f\n",
                    m_nLine.GetStart().GetX(),
                    m_nLine.GetStart().GetY(),
                    m_nLine.GetEnd().GetX(),
                    m_nLine.GetEnd().GetY());
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}

