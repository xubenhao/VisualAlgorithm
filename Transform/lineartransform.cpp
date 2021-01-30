//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "lineartransform.h"

namespace NTransform
{
    LinearTransform::LinearTransform(QObject* parent)
        : Transform(parent)
    {
        m_nOffX = 0.0;
        m_nOffY = 0.0;
    }

    LinearTransform::LinearTransform(
            double nOffX_, 
            double nOffY_, 
            QObject* parent)
       : Transform(parent)
    {
        m_nOffX = nOffX_;
        m_nOffY = nOffY_;
    }

    NMatrix::Matrix LinearTransform::GetMatrix()
    {
        NMatrix::Matrix _mxA;
        _mxA.Offset(m_nOffX, m_nOffY);
        return _mxA;
    }

    Transform* LinearTransform::DeepCopy()
    {
        LinearTransform* _pTrans = new LinearTransform();
        _pTrans->m_nOffX = m_nOffX;
        _pTrans->m_nOffY = m_nOffY;
        return _pTrans;
    }

    void LinearTransform::PrintDebugInfo()
    {
        QString _str;
        _str.sprintf(
                "this is LinearTransform,offX=%.2f,offY=%.2f", 
                m_nOffX, m_nOffY);
        QByteArray ba(_str.toUtf8());
        qWarning("%s",ba.data());
        //qDebug(_str.toLocal8Bit().data());
    }

    void LinearTransform::PrintDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "this is LinearTransform\noffX=%.2f,offY=%.2f\n",
                    m_nOffX, m_nOffY);
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}

