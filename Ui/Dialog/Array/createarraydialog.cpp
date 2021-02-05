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
    Initialize();
}

CreateArrayDialog::~CreateArrayDialog()
{
    delete ui;
}

void CreateArrayDialog::Initialize()
{
    ui->comboBox->addItem(
        QString("10"), 
        QVariant(10));
    ui->comboBox->addItem(
        QString("11"), 
        QVariant(11));
    ui->comboBox->addItem(
        QString("12"), 
        QVariant(12));
    ui->comboBox->addItem(
        QString("13"), 
        QVariant(13));
    ui->comboBox->addItem(
        QString("14"), 
        QVariant(14));

    ui->comboBox->addItem(
        QString("15"), 
        QVariant(15));
    ui->comboBox->addItem(
        QString("16"), 
        QVariant(16));
    ui->comboBox->addItem(
        QString("17"), 
        QVariant(17));
    ui->comboBox->addItem(
        QString("18"), 
        QVariant(18));
    ui->comboBox->addItem(
        QString("19"), 
        QVariant(19));
    connect(
        ui->ok, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(Ok(bool)));
}

void CreateArrayDialog::Ok(bool bFlag_)
{
    QVariant var = ui->comboBox->currentData();
    m_nCapacityt = var.toInt();
    accept();
}
