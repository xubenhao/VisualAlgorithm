//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYORGANIZEWIDGET_H
#define APP_UI_ARRAYORGANIZEWIDGET_H

#include "Ui/header.h"

namespace Ui {
class ArrayOrganizeWidget;
}

class ArrayOrganizeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayOrganizeWidget(QWidget *parent = nullptr);
    ~ArrayOrganizeWidget();

private:
    Ui::ArrayOrganizeWidget *ui;
};

#endif // ARRAYORGANIZEWIDGET_H
