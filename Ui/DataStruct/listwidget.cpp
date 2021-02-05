//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "listwidget.h"
#include "ui_listwidget.h"
#include "Ui/List/listintroducewidget.h"

ListWidget::ListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    Initialize();
}

void ListWidget::Initialize()
{
    connect(ui->restart, SIGNAL(clicked(bool)), this, SLOT(Restart(bool)));
    connect(ui->pre, SIGNAL(clicked(bool)), this, SLOT(Pre(bool)));
    connect(ui->next, SIGNAL(clicked(bool)), this, SLOT(Next(bool)));
    connect(ui->backtopre,
            SIGNAL(clicked(bool)),
            this,
            SLOT(BackToPre(bool)));
    connect(ui->mode,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Mode(bool)));
    QVBoxLayout* _pVBox = new QVBoxLayout();
    QList<QWidget*> listWidgets;
    // to do:
    // initialize pagemanger
    //listWidgets.append(new )
    QWidget* _pWdiget = new ListIntroduceWidget(nullptr);
    _pVBox->addWidget(_pWdiget);
    listWidgets.append(_pWdiget);

    /*_pWdiget = new ArrayOrganizeWidget(nullptr);
    _pVBox->addWidget(_pWdiget);
    listWidgets.append(_pWdiget);

    _pWdiget = new ArrayValueVisitWidget(nullptr);
    _pVBox->addWidget(_pWdiget);
    listWidgets.append(_pWdiget);

    _pWdiget = new ArrayInsertWidget(nullptr);
    _pVBox->addWidget(_pWdiget);
    listWidgets.append(_pWdiget);

    _pWdiget = new ArrayDeleteWidget(nullptr);
    _pVBox->addWidget(_pWdiget);
    listWidgets.append(_pWdiget);
    _pWdiget = new ArraySummaryWidget(nullptr);
    _pVBox->addWidget(_pWdiget);
    listWidgets.append(_pWdiget);*/
    manger = new PageManager(listWidgets, this);
    ui->widget->setLayout(_pVBox);
    manger->ReStart();
}


void ListWidget::Restart(bool checked_)
{
    Q_UNUSED(checked_);
    manger->ReStart();
}

void ListWidget::Pre(bool checked_)
{
    Q_UNUSED(checked_);
    manger->ShowPrePage();
}

void ListWidget::Next(bool checked_)
{
    Q_UNUSED(checked_);
    manger->ShowNextPage();
}

void ListWidget::BackToPre(bool checked_)
{
    // How to do
    // emit signal to parent window,parameter is the name of wanted window
    Q_UNUSED(checked_);
    emit ShowDataStruct(QString("DataStruct"));
    checked_ = true;
}

void ListWidget::Mode(bool checked_)
{
    Q_UNUSED(checked_);
    emit ShowDataStruct(QString("PraticalArrayList"));
    checked_ = true;
}

ListWidget::~ListWidget()
{
    delete ui;
}
