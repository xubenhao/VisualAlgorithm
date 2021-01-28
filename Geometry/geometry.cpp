//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "geometry.h"

namespace NGeometry
{
    Geometry::Geometry(QObject* parent)
        : QObject(parent)
    {

    }

    Geometry::~Geometry()
    {

    }

    void Geometry::Draw(
            NTransform::Transform* pTrans_, 
            QPainter& painter)
    {
        Q_UNUSED(pTrans_);
        Q_UNUSED(painter);
    }

    void Geometry::Draw(QPainter& painter)
    {
        Q_UNUSED(painter);
    }

    void Geometry::Trans(
            NTransform::Transform* pTrans_)
    {
        Q_UNUSED(pTrans_);
    }

    Geometry* Geometry::GetTrans(
            NTransform::Transform* pTrans_)
    {
        Q_UNUSED(pTrans_);
        return nullptr;
    }

    Geometry* Geometry::DeepCopy()
    {
        return nullptr;
    }

    void Geometry::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "This is geometry\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
    }
}

