//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYSUMMARYWIDGET_H
#define APP_UI_ARRAYSUMMARYWIDGET_H

#include "Ui/header.h"

namespace Ui {
class ArraySummaryWidget;
}

class ArraySummaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArraySummaryWidget(QWidget *parent = nullptr);
    ~ArraySummaryWidget();

private:
    Ui::ArraySummaryWidget *ui;
};

#endif // ARRAYSUMMARYWIDGET_H
