//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYINSERTWIDGET_H
#define APP_UI_ARRAYINSERTWIDGET_H

#include "Ui/header.h"

namespace Ui {
class ArrayInsertWidget;
}

class ArrayInsertWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayInsertWidget(QWidget *parent = nullptr);
    ~ArrayInsertWidget();
    void Initialize();
private slots:
    void Insert10AtIndex2(bool bFlag_);
    void Insert11AtIndex5(bool bFlag_);

    void Reset();
    void ProcessTip(NNcShow::NcShowTip* pTip_);

private:
    Ui::ArrayInsertWidget *ui;
};

#endif // ARRAYINSERTWIDGET_H
