//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_MAINWINDOW_H
#define APP_UI_MAINWINDOW_H

#include "header.h"

class DataStructWidget;
class ModelManager;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* Instance();
    ~MainWindow();

    //void AddChildWidget(QWidget* pWidget);

private slots:
    void ShowDataStruct(const QString& strName_);
    void ShowDataStruct(
            const QString& strName_,
            const QVariant& nVar_);

protected:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    void Initialize();

private:
    Ui::MainWindow *ui;
    //DataStructWidget* dataStruct;
    NDataStruct::DynArray<QWidget*> m_arrWidgets;
    NDataStruct::RedBlackTree<QString, QWidget*> m_mapNameToWidget;
    static MainWindow* __instance;
};


#endif // MAINWINDOW_H
