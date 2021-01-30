//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "transform.h"

namespace NTransform
{
    Transform::Transform(QObject* parent)
        : QObject(parent)
    {

    }

    Transform::~Transform()
    {

    }

    NMatrix::Matrix Transform::GetMatrix()
    {
        NMatrix::Matrix _mxA;
        return _mxA;
    }

    Transform* Transform::DeepCopy()
    {
        Transform* _pTrans = new Transform();
        return _pTrans;
    }

    void Transform::PrintDebugInfo()
    {
        qDebug("this it transform");
    }

    void Transform::PrintDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "This it transform\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}

