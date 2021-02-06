//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "datastructwidget.h"
#include "ui_datastructwidget.h"
#include "Functions/datastructfactory.h"
DataStructWidget::DataStructWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataStructWidget)
{
    ui->setupUi(this);
    Initial();
}

DataStructWidget::~DataStructWidget()
{
    delete ui;
}

void DataStructWidget::Initial()
{
    QPair<QString, QString> _arrPairs[2] =
    {
        QPair<QString, QString>("数组", "Array"),
        QPair<QString, QString>("链表", "List"),
    };

    /*QStringList theStrings;
    theStrings << "数组" << "链表" << "栈" << "队列";
    theStrings << "堆" << "优先队列" << "哈希表" << "二叉树";
    theStrings << "二叉搜索树" << "红黑树" << "BTree" << "BPlusTree";
    theStrings << "Graph";*/

    theModel = new QStandardItemModel(this);
    ui->listView->setModel(theModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList::iterator i;
    for (int i = 0; i < 2; i++)
    {
        QStandardItem* pItem = new QStandardItem();
        pItem->setData(_arrPairs[i].first, Qt::DisplayRole);
        pItem->setData(_arrPairs[i].second, Qt::UserRole);
        theModel->appendRow(pItem);
    }

    // register signal-slot
    connect(ui->listView,
            SIGNAL(doubleClicked(QModelIndex)),
            this,
            SLOT(ListClicked(QModelIndex)));
    //connect(this,SIGNAL(DataStructShow(QWidget*)),parent(),SLOT(AddChildWidget(QWidget*)));
}

void DataStructWidget::ListClicked(const QModelIndex& index)
{
    // how to do
    // emit signal to parent's window,parameter is the name of wanted window
    QVariant var = theModel->data(index, Qt::UserRole);
    emit ShowDataStruct(var.toString());
    //DataStructFactory* dataFactor = DataStructFactory::Instance();
    //QWidget* pParent = parentWidget();
    //QWidget* widget = dataFactor->GetDataStructWidget(var.toString(), pParent);
    //MainWindow::Instance()->AddChildWidget(widget);
    //this->hide();
    //widget->show();
}
