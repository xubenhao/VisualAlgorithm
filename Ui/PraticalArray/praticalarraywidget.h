//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef PRATICALARRAYWIDGET_H
#define PRATICALARRAYWIDGET_H

#include "Ui/header.h"

namespace Ui {
class PraticalArrayWidget;
}

class PraticalArrayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PraticalArrayWidget(QWidget *parent = nullptr);
    ~PraticalArrayWidget();
    virtual void showEvent(QShowEvent *event);

Q_SIGNALS:
    void ShowDataStruct(const QString& strName_);
private slots:
    void Pre(bool checked_);
    void ValueSearch(bool checked_);
    void IndexSearch(bool checked_);
    void Insert(bool checked_);
    void Delete(bool checked_);


    void Reset();
    void ProcessTip(NNcShow::NcShowTip* pTip_);
    void Sync(
       int nSize_,
       const NDataStruct::DynArray<QString>& arrValues_);
private:
    void Initialize();
    void ResetControls();
    void InsertCallBack(int nIndex_, const QString& strValue_);
    void DeleteCallBack(int nIndex_);
private:
    Ui::PraticalArrayWidget *ui;

    int m_nCapacity;
    int m_nSize;
    NDataStruct::DynArray<QString> m_arrValues;
    std::function<void()> m_nFinishCallBack;
};

#endif // PRATICALARRAYWIDGET_H
