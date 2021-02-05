//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYINTRODUCEWIDGET_H
#define APP_UI_ARRAYINTRODUCEWIDGET_H

#include "Ui/header.h"

namespace Ui {
class ArrayIntroduceWidget;
}

class ArrayIntroduceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayIntroduceWidget(QWidget *parent = nullptr);
    ~ArrayIntroduceWidget();

private:
    Ui::ArrayIntroduceWidget *ui;
};

#endif // ARRAYINTRODUCEWIDGET_H
