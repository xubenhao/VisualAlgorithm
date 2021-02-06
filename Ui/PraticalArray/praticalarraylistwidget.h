//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_PRATICALARRAYLISTWIDGET_H
#define APP_UI_PRATICALARRAYLISTWIDGET_H
#include "../header.h"

namespace Ui {
class PraticalArrayListWidget;
}



class PraticalArrayListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PraticalArrayListWidget(QWidget *parent = nullptr);
    ~PraticalArrayListWidget();

Q_SIGNALS:
    void ShowDataStruct(
        const QString& strName_,
        const QVariant& nVar_);

private slots:
    void Pre(bool checked_);
    void DeleteArray(bool checked_);
    void CreateArray(bool checked_);
    void ListClicked(const QModelIndex& index);

private:
    void Initialize();
private:
    QStandardItemModel* theModel;

private:
    Ui::PraticalArrayListWidget *ui;
};

#endif // PRATICALARRAYLISTWIDGET_H
