//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayinsertwidget.h"
#include "ui_arrayinsertwidget.h"

const char s_nTipInfo[] =
        "对数组执行元素搜索，\n"
        "会从数组首个元素开始，\n"
        "将待搜索元素，依次与元素内每个元素进行，\n"
        "比较直到找到匹配的元素．";
ArrayInsertWidget::ArrayInsertWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayInsertWidget)
{
    ui->setupUi(this);
    Initialize();
}

void ArrayInsertWidget::Initialize()
{
    //connect(&ui->search4, )
    connect(
        ui->Insert10AtIndex2, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(Insert10AtIndex2(bool)));
    connect(
        ui->Insert11AtIndex5, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(Insert11AtIndex5(bool)));
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

ArrayInsertWidget::~ArrayInsertWidget()
{
    delete ui;
}

void ArrayInsertWidget::Reset()
{
    int i=0;
    i++;
    ui->label->setText(s_nTipInfo);
}

void ArrayInsertWidget::ProcessTip(NNcShow::NcShowTip* pTip_)
{
    int i=0;
    i++;
    ui->label->setText(pTip_->GetTip());
}

void ArrayInsertWidget::Insert10AtIndex2(bool bFlag_)
{
    //Q_UNUSED(checked_);
    // a 2d animation system
    // generate nc file
    ui->widget->Insert10AtIndex2(false);
}

void ArrayInsertWidget::Insert11AtIndex5(bool bFlag_)
{
    //Q_UNUSED(checked_);
    // a 2d animation system
    // generate nc file
    ui->widget->Insert11AtIndex5(false);
}
