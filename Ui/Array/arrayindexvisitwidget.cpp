//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayindexvisitwidget.h"
#include "ui_arrayindexvisitwidget.h"

ArrayIndexVisitWidget::ArrayIndexVisitWidget(
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayIndexVisitWidget)
{
    ui->setupUi(this);
}

ArrayIndexVisitWidget::~ArrayIndexVisitWidget()
{
    delete ui;
}
