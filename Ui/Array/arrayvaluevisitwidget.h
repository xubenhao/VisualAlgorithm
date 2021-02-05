//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYVALUEVISITWIDGET_H
#define APP_UI_ARRAYVALUEVISITWIDGET_H

#include "Ui/header.h"

namespace Ui {
class ArrayValueVisitWidget;
}

class ArrayValueVisitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayValueVisitWidget(QWidget *parent = nullptr);
    ~ArrayValueVisitWidget();
    void Initialize();
private slots:
    void Search4Clicked(bool bFlag_);
    void Search7Clicked(bool bFlag_);

    void on_search4_clicked();
    void Reset();
    void ProcessTip(NNcShow::NcShowTip* pTip_);
private:
    Ui::ArrayValueVisitWidget *ui;
};

#endif // ARRAYVALUEVISITWIDGET_H
