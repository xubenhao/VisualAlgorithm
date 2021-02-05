//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayorganizewidget.h"
#include "ui_arrayorganizewidget.h"

ArrayOrganizeWidget::ArrayOrganizeWidget(
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayOrganizeWidget)
{
    ui->setupUi(this);
}

ArrayOrganizeWidget::~ArrayOrganizeWidget()
{
    delete ui;
}
