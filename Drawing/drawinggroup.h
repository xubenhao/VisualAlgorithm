//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef DRAWING_DRAWINGGROUP_H
#define DRAWING_DRAWINGGROUP_H
#include "drawing.h"
namespace NDrawing
{
    class DrawingGroup : public Drawing
    {
        Q_OBJECT
    public:
        DrawingGroup(QObject *parent = nullptr);
        virtual void Draw(NTransform::Transform* pTrans_, QImage* pImage_);
        void Add(Drawing* pDrawing_){m_arrDrawings.Add(pDrawing_);}
        void Remove(Drawing* pDrawing_){m_arrDrawings.DeleteByValue(pDrawing_);}
        virtual void OutputDebugInfo(QFile& hFile_);
    private:
        NDataStruct::DynArray<Drawing*> m_arrDrawings;
    };
}
#endif // DRAWINGGROUP_H
