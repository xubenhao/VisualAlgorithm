//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYINDEXVISITWIDGET_H
#define APP_UI_ARRAYINDEXVISITWIDGET_H

#include "Ui/header.h"

namespace Ui {
class ArrayIndexVisitWidget;
}

class ArrayIndexVisitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayIndexVisitWidget(QWidget *parent = nullptr);
    ~ArrayIndexVisitWidget();

private:
    Ui::ArrayIndexVisitWidget *ui;
};

#endif // ARRAYINDEXVISITWIDGET_H
