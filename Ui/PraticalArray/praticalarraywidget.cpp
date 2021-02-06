//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "praticalarraywidget.h"
#include "ui_praticalarraywidget.h"
//#include "Ui/Drawing/praticalarraydrawingwidget.h"
PraticalArrayWidget::PraticalArrayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PraticalArrayWidget)
{
    ui->setupUi(this);
    Initialize();
}

PraticalArrayWidget::~PraticalArrayWidget()
{
    delete ui;
}

void PraticalArrayWidget::Initialize()
{

    m_nCapacity = 0;
    connect(ui->pre, SIGNAL(clicked(bool)), this, SLOT(Pre(bool)));
    connect(ui->insertBtn, SIGNAL(clicked(bool)), this, SLOT(Insert(bool)));
    connect(ui->deleteBtn, SIGNAL(clicked(bool)), this, SLOT(Delete(bool)));
    connect(ui->visitBtn, SIGNAL(clicked(bool)), this, SLOT(ValueSearch(bool)));

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
    connect(
        ui->widget,
        SIGNAL(Sync(int, const NDataStruct::DynArray<QString>&)),
        this,
        SLOT(Sync(int, const NDataStruct::DynArray<QString>&)));
}

void PraticalArrayWidget::ResetControls()
{
    /*ui->visitIndex->clear();
    for (int i = 0; i < m_nSize; i++)
    {
        ui->visitIndex->addItem(
            QString::asprintf("%d", i), QVariant(i));
    }*/

    ui->visitValue->clear();
    for (int i = 0; i < m_nSize; i++)
    {
        ui->visitValue->addItem(
            m_arrValues[i], QVariant(m_arrValues[i]));
    }

    QString _strValues[20] =
    {
        "A",
        "B",
        "C",
        "D",
        "E",

        "F",
        "G",
        "H",
        "I",
        "J",

        "K",
        "L",
        "M",
        "N",
        "O",

        "P",
        "Q",
        "R",
        "S",
        "T",
    };

    ui->insertValue->clear();
    bool _arrUsable[20];
    for(int j = 0; j < 20; j++)
    {
        int _nIndex = m_arrValues.Find([&_strValues, j](const QString& strValue_)
        {
            return (strValue_ == _strValues[j]);
        });

        _arrUsable[j] = (_nIndex == -1);
    }

    int _nCount = 0;
    for (int i = 0; i < 5; i++)
    {
        int j = _nCount;
        for (; j < 20; j++)
        {
            if(_arrUsable[j])
            {
                break;
            }
        }

        if(j < 20)
        {
            _nCount = j+1;
            ui->insertValue->addItem(
                _strValues[j], QVariant(_strValues[j]));
        }
        else
        {
            break;
        }
    }

    ui->insertIndex->clear();
    for (int i = 0; i <= m_nSize; i++)
    {
        ui->insertIndex->addItem(
            QString::asprintf("%d", i), QVariant(i));
    }

    ui->deleteIndex->clear();
    for (int i = 0; i < m_nSize; i++)
    {
        ui->deleteIndex->addItem(
            QString::asprintf("%d", i), QVariant(i));
    }
}

void PraticalArrayWidget::Sync(
   int nSize_,
   const NDataStruct::DynArray<QString>& arrValues_)
{
    m_nSize = nSize_;
    m_arrValues = arrValues_;
    ResetControls();
}

void PraticalArrayWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QVariant _nVar = property("ShowData");
    if(_nVar.canConvert<ArrayItem>())
    {
        ArrayItem _nItem = _nVar.value<ArrayItem>();
        int _nId = _nItem.m_nId;
        int _nCapacity = _nItem.m_nCapacity;
        m_nCapacity = _nCapacity;
        m_nSize = 0;
        m_arrValues.DeleteAll();
        ui->widget->ResetShow(_nId, _nCapacity);
    }
    else
    {
        assert(false);
    }


    QWidget::showEvent(event);
}

void PraticalArrayWidget::Pre(bool checked_)
{
    Q_UNUSED(checked_);
    if(ui->widget->GetState() == 1)
    {
        return;
    }

    ui->widget->Save();
    emit ShowDataStruct(QString("PraticalArrayList"));
}

void PraticalArrayWidget::ValueSearch(bool checked_)
{
    if(ui->visitValue->count() == 0)
    {
        return;
    }

    // value+index
    QVariant _nVarValue = ui->visitValue->currentData();
    ui->widget->SearchByValue(_nVarValue.toString());
    m_nFinishCallBack = nullptr;
}

void PraticalArrayWidget::IndexSearch(bool checked_)
{

}

void PraticalArrayWidget::InsertCallBack(int nIndex_, const QString& strValue_)
{
    m_arrValues.Insert(nIndex_, strValue_);
    m_nSize++;
    ResetControls();
}

void PraticalArrayWidget::DeleteCallBack(int nIndex_)
{
    m_arrValues.DeleteByIndex(nIndex_);
    m_nSize--;
    ResetControls();
}

void PraticalArrayWidget::Insert(bool checked_)
{
    if(ui->insertValue->count() == 0)
    {
        return;
    }

    // value+index
    QVariant _nVarValue = ui->insertValue->currentData();
    QVariant _nVarIndex = ui->insertIndex->currentData();
    ui->widget->Insert(
        _nVarIndex.toInt(),
        _nVarValue.toString());
    m_nFinishCallBack = std::bind(
        &PraticalArrayWidget::InsertCallBack,
        this,
        _nVarIndex.toInt(),
        _nVarValue.toString());
}

void PraticalArrayWidget::Delete(bool checked_)
{
    if(ui->deleteIndex->count() == 0)
    {
        return;
    }

    // value+index
    QVariant _nVarIndex = ui->deleteIndex->currentData();
    if(_nVarIndex.toInt() < 0 || _nVarIndex.toInt() >= m_arrValues.GetSize())
    {
        return;
    }

    ui->widget->Delete(
        _nVarIndex.toInt());
    m_nFinishCallBack = std::bind(
        &PraticalArrayWidget::DeleteCallBack,
        this,
        _nVarIndex.toInt());
}

void PraticalArrayWidget::Reset()
{

}

void PraticalArrayWidget::ProcessTip(NNcShow::NcShowTip* pTip_)
{
    if(strcmp(pTip_->GetTip(), "Finish") == 0)
    {
        if(m_nFinishCallBack)
        {
            m_nFinishCallBack();
        }
    }
}



