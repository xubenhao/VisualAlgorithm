//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "rotatetransform.h"

namespace NTransform
{
    RotateTransform::RotateTransform(QObject* parent)
        : Transform(parent)
    {
        m_nAngle = 0.0;
    }

    RotateTransform::RotateTransform(
            NStruct::Point poCenter_, 
            double nAngle_, 
            QObject* parent)
        : Transform(parent)
    {
        m_poCenter = poCenter_;
        m_nAngle = nAngle_;
    }

    NMatrix::Matrix RotateTransform::GetMatrix()
    {
        NMatrix::Matrix _mxA;
        _mxA.Offset(m_poCenter.GetX(), m_poCenter.GetY());
        _mxA.Rotate(m_nAngle);
        _mxA.Offset(
                -1.0 * m_poCenter.GetX(), 
                -1.0 * m_poCenter.GetY());
        return _mxA;
    }

    Transform* RotateTransform::DeepCopy()
    {
        RotateTransform* _pTrans = new RotateTransform();
        _pTrans->m_poCenter = m_poCenter;
        _pTrans->m_nAngle = m_nAngle;
        return _pTrans;
    }

    void RotateTransform::PrintDebugInfo()
    {
        QString _str;
        _str.sprintf(
                "this is RotateTransform,Cente.x=%.2f,Center.y=%.2f,Angle=%.2f\n",
                
                m_poCenter.GetX(), 
                m_poCenter.GetY(), 
                m_nAngle);

        QByteArray ba(_str.toUtf8());
        qWarning("%s",ba.data());
    }

    void RotateTransform::PrintDebugInfo(QFile& hFile_)
    {
        QString _str;
        _str.sprintf(
                "this is RotateTransform\nCente.x=%.2f,Center.y=%.2f,Angle=%.2f\n",
                     
                m_poCenter.GetX(), 
                m_poCenter.GetY(), 
                m_nAngle);

        QByteArray ba(_str.toUtf8());
        hFile_.write(ba);
        hFile_.flush();
    }
}

