//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYDELETEWIDGET_H
#define APP_UI_ARRAYDELETEWIDGET_H

#include "Ui/header.h"

namespace Ui {
class ArrayDeleteWidget;
}

class ArrayDeleteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayDeleteWidget(QWidget *parent = nullptr);
    ~ArrayDeleteWidget();
    void Initialize();
private slots:
    void DeleteAtIndex0(bool bFlag_);
    void DeleteAtIndex2(bool bFlag_);
    void DeleteAtIndex4(bool bFlag_);

    void Reset();
    void ProcessTip(NNcShow::NcShowTip* pTip_);

private:
    Ui::ArrayDeleteWidget *ui;
};

#endif // ARRAYDELETEWIDGET_H
