//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_CREATEARRAYDIALOG_H
#define APP_UI_CREATEARRAYDIALOG_H

#include "Ui/header.h"

namespace Ui {
class CreateArrayDialog;
}

class CreateArrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateArrayDialog(QWidget *parent = nullptr);
    ~CreateArrayDialog();

    int GetCapacity(){return m_nCapacityt;}
private:
    void Initialize();

private slots:
    void Ok(bool);

private:
    Ui::CreateArrayDialog *ui;

private:
    int m_nCapacityt;
};

#endif // CREATEARRAYDIALOG_H
