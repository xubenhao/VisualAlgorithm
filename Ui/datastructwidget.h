//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_DATASTRUCTWIDGET_H
#define APP_UI_DATASTRUCTWIDGET_H
#include "header.h"

namespace Ui {
class DataStructWidget;
}

class DataStructWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataStructWidget(QWidget *parent = nullptr);
    ~DataStructWidget();

Q_SIGNALS:
    void ShowDataStruct(const QString& strName_);

private:
    void Initial();
private slots:
    void ListClicked(const QModelIndex& index);

signals:
    void DataStructShow(QWidget*);

private:
    QStandardItemModel* theModel;

private:
    Ui::DataStructWidget *ui;
};

#endif // DATASTRUCTWIDGET_H
