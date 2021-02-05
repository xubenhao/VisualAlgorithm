//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arraydeletewidget.h"
#include "ui_arraydeletewidget.h"

const char s_nTipInfo[] =
        "";
ArrayDeleteWidget::ArrayDeleteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayDeleteWidget)
{
    ui->setupUi(this);
    Initialize();
}

void ArrayDeleteWidget::Initialize()
{
    //connect(&ui->search4, )
    connect(
        ui->DeleteAt0, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(DeleteAtIndex0(bool)));
    connect(
        ui->DeleteAt2, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(DeleteAtIndex2(bool)));
    connect(
        ui->DeleteAt4, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(DeleteAtIndex4(bool)));

    connect(
        ui->widget, 
        SIGNAL(Reset()), 
        this, 
        SLOT(Reset()));
    connect(
        ui->widget, 
        SIGNAL(ProcessTip(NNcShow::NcShowTip*)), 
        this, 
        SLOT(ProcessTip(NNcShow::NcShowTip*)));
}

ArrayDeleteWidget::~ArrayDeleteWidget()
{
    delete ui;
}

void ArrayDeleteWidget::Reset()
{
    int i=0;
    i++;
}

void ArrayDeleteWidget::ProcessTip(NNcShow::NcShowTip* pTip_)
{
    int i=0;
    i++;
    ui->label->setText(pTip_->GetTip());
}

void ArrayDeleteWidget::DeleteAtIndex0(bool bFlag_)
{
    //Q_UNUSED(checked_);
    // a 2d animation system
    // generate nc file
    ui->widget->DeleteAtIndex0(false);
}

void ArrayDeleteWidget::DeleteAtIndex2(bool bFlag_)
{
    //Q_UNUSED(checked_);
    // a 2d animation system
    // generate nc file
    ui->widget->DeleteAtIndex2(false);
}

void ArrayDeleteWidget::DeleteAtIndex4(bool bFlag_)
{
    //Q_UNUSED(checked_);
    // a 2d animation system
    // generate nc file
    ui->widget->DeleteAtIndex4(false);
}
