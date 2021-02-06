//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PraticalArray/praticalarraylistwidget.h"
#include "PraticalArray/praticalarraywidget.h"
#include "Ui/DataStruct/listwidget.h"

MainWindow* MainWindow::__instance = nullptr;
MainWindow* MainWindow::Instance()
{
    if(__instance == nullptr)
    {
        __instance = new MainWindow();
    }

    return __instance;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Initialize()
{
    NModelManager::ModelManager::Instance()->GeneralArrayModelGenerate();
    //NNcManager::NcManager::Instance()->ArrayGenerateForDelete()
    // Parent Manager His Child Pages

    // How to do
    // create all child windows

    // datastruct window
    DataStructWidget* _pDataWidget = new DataStructWidget(this);
    ui->horizontalLayout->addWidget(_pDataWidget);
    m_arrWidgets.Add(_pDataWidget);
    NDataStruct::RedBlackTree<QString, QWidget*>::Pair _nPair;
    _nPair.m_nKey = QString("DataStruct");
    _nPair.m_nValue = _pDataWidget;
    m_mapNameToWidget.Add(_nPair);

    connect(_pDataWidget,
            SIGNAL(ShowDataStruct(const QString&)),
            this,
            SLOT(ShowDataStruct(const QString&)));

    // array window
    ArrayWidget* _pArrWidget = new ArrayWidget(this);
    _pArrWidget->hide();
    ui->horizontalLayout->addWidget(_pArrWidget);
    m_arrWidgets.Add(_pArrWidget);
    _nPair.m_nKey = QString("Array");
    _nPair.m_nValue = _pArrWidget;
    m_mapNameToWidget.Add(_nPair);

    connect(_pArrWidget,
            SIGNAL(ShowDataStruct(const QString&)),
            this,
            SLOT(ShowDataStruct(const QString&)));


    ListWidget* _pListWidget = new ListWidget(this);
    _pListWidget->hide();
    ui->horizontalLayout->addWidget(_pListWidget);
    m_arrWidgets.Add(_pListWidget);
    _nPair.m_nKey = QString("List");
    _nPair.m_nValue = _pListWidget;
    m_mapNameToWidget.Add(_nPair);

    connect(_pListWidget,
            SIGNAL(ShowDataStruct(const QString&)),
            this,
            SLOT(ShowDataStruct(const QString&)));


    // pratical-array-list
    PraticalArrayListWidget* _pPraArrListWidget = new PraticalArrayListWidget(this);
    _pPraArrListWidget->hide();
    ui->horizontalLayout->addWidget(_pPraArrListWidget);
    m_arrWidgets.Add(_pPraArrListWidget);
    _nPair.m_nKey = QString("PraticalArrayList");
    _nPair.m_nValue = _pPraArrListWidget;
    m_mapNameToWidget.Add(_nPair);

    connect(_pPraArrListWidget,
            SIGNAL(ShowDataStruct(const QString&, const QVariant&)),
            this,
            SLOT(ShowDataStruct(const QString&, const QVariant&)));

    // pratical-array-window
    PraticalArrayWidget* _pPraArrWidget = new PraticalArrayWidget(this);
    _pPraArrWidget->hide();
    ui->horizontalLayout->addWidget(_pPraArrWidget);
    m_arrWidgets.Add(_pPraArrWidget);
    _nPair.m_nKey = QString("PraticalArray");
    _nPair.m_nValue = _pPraArrWidget;
    m_mapNameToWidget.Add(_nPair);

    connect(_pPraArrWidget,
            SIGNAL(ShowDataStruct(const QString&)),
            this,
            SLOT(ShowDataStruct(const QString&)));
    // and build the mapping for window's name and its pointer
    // and initize the initial show
}

void MainWindow::ShowDataStruct(const QString& strName_)
{
    for(int i = 0; i < m_arrWidgets.GetSize(); i++)
    {
        m_arrWidgets[i]->hide();
    }

    NDataStruct::RedBlackTree<QString, QWidget*>::Node* _pNode = nullptr;
    _pNode = m_mapNameToWidget.Find(strName_);
    assert(_pNode);
    _pNode->GetPair().m_nValue->show();
}

void MainWindow::ShowDataStruct(
        const QString& strName_,
        const QVariant& nVar_)
{
    for(int i = 0; i < m_arrWidgets.GetSize(); i++)
    {
        m_arrWidgets[i]->hide();
    }

    NDataStruct::RedBlackTree<QString, QWidget*>::Node* _pNode = nullptr;
    _pNode = m_mapNameToWidget.Find(strName_);
    assert(_pNode);

    _pNode->GetPair().m_nValue->setProperty("ShowData", nVar_);
    _pNode->GetPair().m_nValue->show();
}



/*void MainWindow::AddChildWidget(QWidget* pWidget)
{
    //ui->horizontalLayout->removeWidget(pWidget);
    ui->horizontalLayout->addWidget(pWidget);
}*/
