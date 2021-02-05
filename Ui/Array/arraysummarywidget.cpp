//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arraysummarywidget.h"
#include "ui_arraysummarywidget.h"

ArraySummaryWidget::ArraySummaryWidget(
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArraySummaryWidget)
{
    ui->setupUi(this);
}

ArraySummaryWidget::~ArraySummaryWidget()
{
    delete ui;
}
