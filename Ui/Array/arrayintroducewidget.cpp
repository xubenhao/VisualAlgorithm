//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayintroducewidget.h"
#include "ui_arrayintroducewidget.h"

ArrayIntroduceWidget::ArrayIntroduceWidget(
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayIntroduceWidget)
{
    ui->setupUi(this);
}

ArrayIntroduceWidget::~ArrayIntroduceWidget()
{
    delete ui;
}
