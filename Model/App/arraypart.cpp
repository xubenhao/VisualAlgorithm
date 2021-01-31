//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arraypart.h"

namespace NModel
{
    ArrayPart::ArrayPart(ARRAY_TYPE nType_, QObject* parent)
        : MovablePart(parent)
    {
        m_nType = nType_;
        strncpy(m_strName, "Scale", sizeof(m_strName));
    }

    void ArrayPart::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "ArrayPart\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
        MovablePart::OutputDebugInfo(hFile_);
    }
}
