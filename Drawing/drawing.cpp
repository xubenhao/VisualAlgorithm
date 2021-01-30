//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "drawing.h"

namespace NDrawing
{
    Drawing::Drawing(QObject *parent)
        :QObject(parent)
    {
        m_pGeometry = nullptr;
    }

    // 绘制可以绘制在窗口表面，
    // 也可以绘制在位图表面
    // 为了提供更多灵活性，
    // 及使用多个缓冲区策略，
    // 绘制一般基于位图表面绘制
    // 拥有绘制对象的窗口可以获取绘制结果，
    // 按自己需求进行使用
    void Drawing::Draw(
            NTransform::Transform* pTrans_, 
            QImage* pImage_)
    {
        if(pImage_ == nullptr)
        {
            return;
        }

        QPainter painter(pImage_);
        painter.setPen(m_Pen);
        painter.setBrush(m_Brush);
        painter.setFont(m_Font);
        m_pGeometry->Draw(pTrans_, painter);
    }

    void Drawing::OutputDebugInfo(QFile& hFile_)
    {
        // Output Geometry Info
        m_pGeometry->OutputDebugInfo(hFile_);
        // Output Brush Info
        // Output Pen Info
        // Output Font Info
    }
}

