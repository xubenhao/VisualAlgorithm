//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef DRAWING_DRAWING_H
#define DRAWING_DRAWING_H
#include "header.h"
namespace NDrawing
{
    class Drawing : public QObject
    {
        Q_OBJECT
    public:
        Drawing(QObject *parent = nullptr);
        virtual void Draw(NTransform::Transform* pTrans_, QImage* pImage_);
        void SetGeometry(NGeometry::Geometry* pGeometry_){m_pGeometry = pGeometry_;}
        NGeometry::Geometry* GetGeometry(){return m_pGeometry;}
        void SetPen(QPen nPen){m_Pen = nPen;}
        QPen GetPen(){return m_Pen;}
        void SetBrush(QBrush nBrush){m_Brush = nBrush;}
        QBrush GetBrush(){return m_Brush;}
        void SetFont(QFont nFont){m_Font = nFont;}
        QFont GetFont(){return m_Font;}
        virtual void OutputDebugInfo(QFile& hFile_);
    private:
        NGeometry::Geometry* m_pGeometry;
        QPen m_Pen;
        QBrush m_Brush;
        QFont m_Font;
    };
}

#endif // DRAWING_H
