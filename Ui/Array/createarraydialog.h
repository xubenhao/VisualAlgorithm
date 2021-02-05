//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef CREATEARRAYDIALOG_H
#define CREATEARRAYDIALOG_H

#include <QDialog>

namespace Ui {
class CreateArrayDialog;
}

class CreateArrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateArrayDialog(QWidget *parent = nullptr);
    ~CreateArrayDialog();

private:
    Ui::CreateArrayDialog *ui;
};

#endif // CREATEARRAYDIALOG_H
