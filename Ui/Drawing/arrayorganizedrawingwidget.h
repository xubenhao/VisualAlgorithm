//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYORGANIZEDRAWINGWIDGET_H
#define APP_UI_ARRAYORGANIZEDRAWINGWIDGET_H

#include "Ui/header.h"

class ArrayOrganizeDrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ArrayOrganizeDrawingWidget(QWidget *parent = nullptr);
    void Initialize();

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void ResetAllParts();
    void AdjustInitialTransform();
private:
    NDataStruct::DynArray<NModel::Part*> m_arrEleParts;
    NDataStruct::DynArray<NModel::Part*> m_arrEleBackGroundParts;

    NDataStruct::DynArray<NModel::Part*> m_arrEleAddrParts;
    NDataStruct::DynArray<NModel::Part*> m_arrParts;
    //NDataStruct::DynArray<NModel::Part*> m_arrEleIndexParts;

};

#endif // ARRAYORGANIZEDRAWINGWIDGET_H
