//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "drawinggroup.h"

namespace NDrawing
{
    DrawingGroup::DrawingGroup(QObject *parent)
        :Drawing(parent)
    {

    }

    void DrawingGroup::Draw(
            NTransform::Transform* pTrans_, 
            QImage* pImage_)
    {
        int _nSize = m_arrDrawings.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            m_arrDrawings[i]->Draw(pTrans_, pImage_);
        }
    }

    void DrawingGroup::OutputDebugInfo(QFile& hFile_)
    {
        for(int i = 0; i < m_arrDrawings.GetSize(); i++)
        {
            m_arrDrawings[i]->OutputDebugInfo(hFile_);
        }
    }
}


