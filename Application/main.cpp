//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow::Instance()->setWindowTitle("数据结构＆算法可视化");
    MainWindow::Instance()->show();
    // w.show();
    return a.exec();
}
