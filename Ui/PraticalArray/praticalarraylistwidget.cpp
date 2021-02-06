//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "praticalarraylistwidget.h"
#include "ui_praticalarraylistwidget.h"
#include "Ui/Dialog/Array/createarraydialog.h"
PraticalArrayListWidget::PraticalArrayListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PraticalArrayListWidget)
{
    ui->setupUi(this);
    Initialize();
}

PraticalArrayListWidget::~PraticalArrayListWidget()
{
    delete ui;
}

void PraticalArrayListWidget::Initialize()
{
    connect(ui->pre, SIGNAL(clicked(bool)), this, SLOT(Pre(bool)));
    connect(ui->deleteArray, SIGNAL(clicked(bool)), this, SLOT(DeleteArray(bool)));
    connect(ui->createArray, SIGNAL(clicked(bool)), this, SLOT(CreateArray(bool)));

    theModel = new QStandardItemModel(this);
    ui->listView->setModel(theModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /*QStringList::iterator i;
    for (int i = 0; i < 2; i++)
    {
        QStandardItem* pItem = new QStandardItem();
        pItem->setData(_arrPairs[i].first, Qt::DisplayRole);
        pItem->setData(_arrPairs[i].second, Qt::UserRole);
        theModel->appendRow(pItem);
    }*/

    // register signal-slot
    connect(ui->listView,
            SIGNAL(doubleClicked(QModelIndex)),
            this,
            SLOT(ListClicked(QModelIndex)));
}

void PraticalArrayListWidget::Pre(bool checked_)
{
    Q_UNUSED(checked_);
    emit ShowDataStruct(QString("Array"), QVariant());
}

void PraticalArrayListWidget::DeleteArray(bool checked_)
{
    Q_UNUSED(checked_);
    QModelIndex _nIndex = ui->listView->currentIndex();
    QStandardItem* _pItem = theModel->itemFromIndex(_nIndex);
    int _nId = _nIndex.row();
    if(_nId < 0 || _nId >= theModel->rowCount())
    {
        return;
    }

    QVariant _nVar = _pItem->data(Qt::UserRole);
    int _nCapacity = _nVar.toInt();
    QString _strFile = NModelManager::ModelManager::GetPraticalArrayModelFilePath(_nId, _nCapacity);
    QFile::remove(_strFile);
    theModel->removeRow(_nId);
}

void PraticalArrayListWidget::CreateArray(bool checked_)
{
    Q_UNUSED(checked_);
    CreateArrayDialog *_pCreateArrDia = new CreateArrayDialog(this);
    int _nRet = _pCreateArrDia->exec();
    if(_nRet == QDialog::Accepted)
    {
        int _nCapacity = _pCreateArrDia->GetCapacity();
        QStandardItem* pItem = new QStandardItem();
        pItem->setData(_nCapacity, Qt::DisplayRole);
        pItem->setData(_nCapacity, Qt::UserRole);
        theModel->appendRow(pItem);
    }

    delete _pCreateArrDia;
}

void PraticalArrayListWidget::ListClicked(const QModelIndex& index)
{
    Q_UNUSED(index);
    QVariant var = theModel->data(index, Qt::UserRole);
    int _nCapacity = var.toInt();
    ArrayItem _nItem;
    _nItem.m_nCapacity = _nCapacity;
    _nItem.m_nId = index.row();

    emit ShowDataStruct(
        QString("PraticalArray"),
        QVariant::fromValue(_nItem));
}
