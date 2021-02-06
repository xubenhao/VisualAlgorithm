//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef LISTINTRODUCEWIDGET_H
#define LISTINTRODUCEWIDGET_H

#include <QWidget>

namespace Ui {
class ListIntroduceWidget;
}

class ListIntroduceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListIntroduceWidget(QWidget *parent = nullptr);
    ~ListIntroduceWidget();

private:
    Ui::ListIntroduceWidget *ui;
};

#endif // LISTINTRODUCEWIDGET_H
