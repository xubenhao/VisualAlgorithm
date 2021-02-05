//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayvaluevisitwidget.h"
#include "ui_arrayvaluevisitwidget.h"

const char s_nTipInfo[] =
        "对数组执行元素搜索，\n"
        "会从数组首个元素开始，\n"
        "将待搜索元素，依次与元素内每个元素进行，\n"
        "比较直到找到匹配的元素．";

ArrayValueVisitWidget::ArrayValueVisitWidget(
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArrayValueVisitWidget)
{
    ui->setupUi(this);
    Initialize();
}

void ArrayValueVisitWidget::Initialize()
{
    //connect(&ui->search4, )
    connect(
        ui->search4, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(Search4Clicked(bool)));
    connect(
        ui->search7, 
        SIGNAL(clicked(bool)), 
        this, 
        SLOT(Search7Clicked(bool)));
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

ArrayValueVisitWidget::~ArrayValueVisitWidget()
{
    delete ui;
}

void ArrayValueVisitWidget::Reset()
{
    int i=0;
    i++;
    ui->label->setText(s_nTipInfo);
}

void ArrayValueVisitWidget::ProcessTip(NNcShow::NcShowTip* pTip_)
{
    int i=0;
    i++;
    ui->label->setText(pTip_->GetTip());
}

void ArrayValueVisitWidget::Search4Clicked(bool bFlag_)
{
    //Q_UNUSED(checked_);
    // a 2d animation system
    // generate nc file
    ui->widget->Search4Clicked(false);
}

void ArrayValueVisitWidget::Search7Clicked(bool bFlag_)
{
    //Q_UNUSED(checked_);
    // a 2d animation system
    // generate nc file
    ui->widget->Search7Clicked(false);
}

void ArrayValueVisitWidget::on_search4_clicked()
{
}
