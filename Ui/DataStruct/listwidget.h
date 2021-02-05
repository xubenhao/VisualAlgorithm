//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_LISTWIDGET_H
#define APP_UI_LISTWIDGET_H

#include "Ui/header.h"
class PageManager;

namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget();


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
    Ui::ListWidget *ui;
    PageManager* manger;
};

#endif // LISTWIDGET_H
