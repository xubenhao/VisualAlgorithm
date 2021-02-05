//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FUNCTIONS_PAGEMANAGER_H
#define FUNCTIONS_PAGEMANAGER_H

#include "header.h"

class PageManager : public QObject
{
    Q_OBJECT
public:
    explicit PageManager(QList<QWidget*> listWidget_, QObject *parent = nullptr);
    ~PageManager();

    void ShowPrePage();
    void ShowNextPage();
    void ReStart();

private:
    int m_nCurIndex;
    QList<QWidget*> m_listWidgets;

};
#endif // PAGEMANAGER_H
