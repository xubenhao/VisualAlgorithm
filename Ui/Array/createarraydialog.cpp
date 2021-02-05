//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "createarraydialog.h"
#include "ui_createarraydialog.h"

CreateArrayDialog::CreateArrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateArrayDialog)
{
    ui->setupUi(this);
}

CreateArrayDialog::~CreateArrayDialog()
{
    delete ui;
}
