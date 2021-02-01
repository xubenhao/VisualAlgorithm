//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arraymodelfilegenerate.h"

namespace NFileGenerate
{
    ArrayModelFileGenerate::ArrayModelFileGenerate(QObject* object)
        : ModelFileGenerate(object)
    {

    }

    int ArrayModelFileGenerate::Generate(const QString& filePath_)
    {
       m_file.close();
       m_file.setFileName(filePath_);
       bool _bRet = m_file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
       if(!_bRet)
       {
           return ACCESS_ERROR;
       }

       WriteArrayModel(0);
       WriteArray(0);
       //int _nSize = m_nParam.m_arrElements.GetSize();
       for(int i = 0; i < m_nParam.m_nCapacity; i++)
       {
           // Element
           if(i < m_nParam.m_nSize)
           {
               WriteElement(m_nParam.m_arrElements[i]);
           }
           else
           {
               WriteElement(NParameter::Element());
           }

           // ElementAddress
           WriteElementAddress(m_nParam.m_arrElementAddresses[i]);
           // ElementIndex
           WriteElementIndex(m_nParam.m_arrElementIndexes[i]);
       }

       WriteArray(1);
       WriteArrayModel(1);
       m_file.flush();
       m_file.close();
       return SUCCESS;
    }

    void ArrayModelFileGenerate::WriteArrayModel(int nFlag_)
    {
        if(nFlag_ == 0)
        {
            QString _str = QString::asprintf("<ArrayModel>\n");
            QByteArray _nByteArr = _str.toUtf8();
            qint64 num = m_file.write(_nByteArr);
            qDebug("%lld", num);
        }
        else
        {
            QString _str = QString::asprintf("</ArrayModel>\n");
            QByteArray _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
        }
    }

    void ArrayModelFileGenerate::WriteArray(int nFlag_)
    {
        if(nFlag_ == 0)
        {
            QString _str = QString::asprintf(
                "<Array " \
                "Capacity=%d, " \
                "Size=%d, " \
                "ElementSize.Width=%f, ElementSize.Height=%f, " \
                "Pen.Color=%d, Pen.Width=%f, " \
                "Point.X=%.f, Point.Y=%f, " \
                "Brush.Color=%d, " \
                "Font.Family=\"%s\", Font.PointSize=%d, Font.Weight=%d, Font.Italic=%d, " \
                ">\n",
                m_nParam.m_nCapacity,
                m_nParam.m_nSize,
                m_nParam.m_nElementSize.m_nWidth,
                m_nParam.m_nElementSize.m_nHeight,
                NParameter::ColorToInt(m_nParam.m_nPen.m_nColor),
                m_nParam.m_nPen.m_nWidth,
                m_nParam.m_poStart.GetX(),
                m_nParam.m_poStart.GetY(),
                NParameter::ColorToInt(m_nParam.m_nBrush.m_nColor),
                m_nParam.m_nFont.m_strFamily,
                m_nParam.m_nFont.m_nPointSize,
                m_nParam.m_nFont.m_nWeight,
                m_nParam.m_nFont.m_bItalic);
            QByteArray _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
        }
        else
        {
            QString _str = QString::asprintf("</Array>\n");
            QByteArray _nByteArr = _str.toUtf8();
            m_file.write(_nByteArr);
        }
    }

    void ArrayModelFileGenerate::WriteElement(const NParameter::Element& nElement_)
    {
        QString _str;
        if(nElement_.m_nPosition.m_nMoveType == NModel::MOVE_TYPE::LINEAR)
        {
            _str = QString::asprintf(
                "<Element " \
                "Name=\"%s\", " \
                "Content=\"%s\", " \
                "Brush.Color=%d, " \
                "Pen.Color=%d, Pen.Width=%.f, " \
                "Font.Family=\"%s\", Font.PointSize=%d, Font.Weight=%d, Font.Italic=%d, " \
                "MoveType=%d, CurPos=%.f, Angle=%.f," \
                "/>\n",
                nElement_.m_strName,
                nElement_.m_nContent,
                NParameter::ColorToInt(nElement_.m_nBrush.m_nColor),
                NParameter::ColorToInt(nElement_.m_nPen.m_nColor),
                nElement_.m_nPen.m_nWidth,
                nElement_.m_nFont.m_strFamily,
                nElement_.m_nFont.m_nPointSize,
                nElement_.m_nFont.m_nWeight,
                nElement_.m_nFont.m_bItalic,
                nElement_.m_nPosition.m_nMoveType,
                nElement_.m_nPosition.m_nPosition.m_nLinearPos.m_nCurPosition,
                nElement_.m_nPosition.m_nPosition.m_nLinearPos.m_nAngle);
        }
        else if(nElement_.m_nPosition.m_nMoveType == NModel::MOVE_TYPE::ROTATE)
        {
            _str = QString::asprintf(
                "<Element " \
                "Name=\"%s\", " \
                "Content=\"%s\", " \
                "Brush.Color=%d, " \
                "Pen.Color=%d, Pen.Width=%.f, " \
                "Font.Family=\"%s\", Font.PointSize=%d, Font.Weight=%d, Font.Italic=%d, " \
                "MoveType=%d, CenterX=%.f, CenterY=%.f, Radius=%.f, Angle=%.f" \
                "/>\n",
                nElement_.m_strName,
                nElement_.m_nContent,
                NParameter::ColorToInt(nElement_.m_nBrush.m_nColor),
                NParameter::ColorToInt(nElement_.m_nPen.m_nColor),
                nElement_.m_nPen.m_nWidth,
                nElement_.m_nFont.m_strFamily,
                nElement_.m_nFont.m_nPointSize,
                nElement_.m_nFont.m_nWeight,
                nElement_.m_nFont.m_bItalic,
                nElement_.m_nPosition.m_nMoveType,
                nElement_.m_nPosition.m_nPosition.m_nRotatePos.m_poCenter.GetX(),
                nElement_.m_nPosition.m_nPosition.m_nRotatePos.m_poCenter.GetY(),
                nElement_.m_nPosition.m_nPosition.m_nRotatePos.m_nRadius,
                nElement_.m_nPosition.m_nPosition.m_nRotatePos.m_nAngle);
        }
        else
        {
            assert(false);
        }

        QByteArray _nByteArr = _str.toUtf8();
        m_file.write(_nByteArr);
    }

    void ArrayModelFileGenerate::WriteElementAddress(const NParameter::ElementAddress& nElementAddress_)
    {
        QString _str = QString::asprintf(
            "<ElementAddress " \
            "ArrowLen1=%f, " \
            "ArrowLen2=%f, " \
            "Size.Height=%.f, Size.Width=%f, " \
            "Content=\"%s\", " \
            "Pen.Color=%d, Pen.Width=%.f, " \
            "Brush.Color=%d, " \
            "Font.Family=\"%s\", Font.PointSize=%d, Font.Weight=%d, Font.Italic=%d, " \
            "/>\n",
            nElementAddress_.m_nArrowLen1,
            nElementAddress_.m_nArrowLen2,
            nElementAddress_.m_nSize.m_nHeight,
            nElementAddress_.m_nSize.m_nWidth,
            nElementAddress_.m_nContent,
            NParameter::ColorToInt(nElementAddress_.m_nPen.m_nColor),
            nElementAddress_.m_nPen.m_nWidth,
            NParameter::ColorToInt(nElementAddress_.m_nBrush.m_nColor),
            nElementAddress_.m_nFont.m_strFamily,
            nElementAddress_.m_nFont.m_nPointSize,
            nElementAddress_.m_nFont.m_nWeight,
            nElementAddress_.m_nFont.m_bItalic ? 1 : 0);
        QByteArray _nByteArr = _str.toUtf8();
        m_file.write(_nByteArr);
    }

    void ArrayModelFileGenerate::WriteElementIndex(const NParameter::ElementIndex& nElementIndex_)
    {
        QString _str = QString::asprintf(
            "<ElementIndex " \
            "HorizontalLen=%f, " \
            "VerticalLen=%f, " \
            "Size.Height=%.f, Size.Width=%.f, " \
            "Content=\"%s\", " \
            "Pen.Color=%d, Pen.Width=%.f, " \
            "Brush.Color=%d, " \
            "Font.Family=\"%s\", Font.PointSize=%d, Font.Weight=%d, Font.Italic=%d, " \
            "/>\n",
            nElementIndex_.m_nHorizontalLen,
            nElementIndex_.m_nVerticalLen,
            nElementIndex_.m_nSize.m_nHeight,
            nElementIndex_.m_nSize.m_nWidth,
            nElementIndex_.m_nContent,
            NParameter::ColorToInt(nElementIndex_.m_nPen.m_nColor),
            nElementIndex_.m_nPen.m_nWidth,
            NParameter::ColorToInt(nElementIndex_.m_nBrush.m_nColor),
            nElementIndex_.m_nFont.m_strFamily,
            nElementIndex_.m_nFont.m_nPointSize,
            nElementIndex_.m_nFont.m_nWeight,
            nElementIndex_.m_nFont.m_bItalic ? 1 : 0);
        QByteArray _nByteArr = _str.toUtf8();
        m_file.write(_nByteArr);
    }
}



