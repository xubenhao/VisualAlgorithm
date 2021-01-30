//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "scaletransform.h"


namespace NTransform
{
    ScaleTransform::ScaleTransform(QObject* parent)
        : Transform(parent)
    {
        m_nScaleX = 1.0;
        m_nScaleY = 1.0;
    }

    NMatrix::Matrix ScaleTransform::GetMatrix()
    {
        NMatrix::Matrix _mxA;
        _mxA.Scale(m_nScaleX, m_nScaleY);
        return _mxA;
    }

    Transform* ScaleTransform::DeepCopy()
    {
        ScaleTransform* _pTrans = new ScaleTransform();
        _pTrans->m_nScaleX = m_nScaleX;
        _pTrans->m_nScaleY = m_nScaleY;
        return _pTrans;
    }

    void ScaleTransform::PrintDebugInfo()
    {
        QString _str;
        _str.sprintf(
                "this is ScaleTransform,Scale.x=%.2f, Scale.y=%.2f\n",
                
                m_nScaleX, 
                m_nScaleY);

        QByteArray ba(_str.toUtf8());
        qWarning("%s",ba.data());
    }

    void ScaleTransform::PrintDebugInfo(QFile& hFile_)
    {
        QString _str;
        _str.sprintf(
                "this is ScaleTransform\n Scale.x=%.2f, Scale.y=%.2f\n",
                
                m_nScaleX, 
                m_nScaleY);

        QByteArray ba(_str.toUtf8());
        hFile_.write(ba);
        hFile_.flush();
    }
}

