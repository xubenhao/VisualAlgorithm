//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYWIDGET_H
#define APP_UI_ARRAYWIDGET_H

#include "Ui/header.h"
class PageManager;
namespace Ui {
class ArrayWidget;
}

class ArrayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayWidget(QWidget *parent = nullptr);
    ~ArrayWidget();

private:
    void Initialize();

Q_SIGNALS:
    void ShowDataStruct(const QString& strName_);

private slots:
    void Restart(bool checked_);
    void Pre(bool checked_);
    void Next(bool checked_);
    void BackToPre(bool checked_);
    void Mode(bool checked_);

private:
    Ui::ArrayWidget *ui;
    PageManager* manger;
};

#endif // ARRAYWIDGET_H
