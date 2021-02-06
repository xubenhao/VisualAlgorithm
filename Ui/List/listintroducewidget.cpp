//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "listintroducewidget.h"
#include "ui_listintroducewidget.h"

ListIntroduceWidget::ListIntroduceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListIntroduceWidget)
{
    ui->setupUi(this);
}

ListIntroduceWidget::~ListIntroduceWidget()
{
    delete ui;
}
