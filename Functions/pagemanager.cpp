//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "pagemanager.h"

PageManager::PageManager(
        QList<QWidget*> listWidget_, 
        QObject *parent_)
    : QObject(parent_)
{
    m_listWidgets = listWidget_;
    m_nCurIndex = -1;
    int size = m_listWidgets.size();
    for(int i = 0; i < size; i++)
    {
        m_listWidgets[i]->hide();
    }
}

PageManager::~PageManager()
{
    int size = m_listWidgets.size();
    for(int i = 0; i < size; i++)
    {
        if(m_listWidgets[i]->parentWidget() == nullptr)
        {
            delete m_listWidgets[i];
            m_listWidgets[i] = nullptr;
        }
    }
}

void PageManager::ReStart()
{
    int size = m_listWidgets.size();
    if(size <= 0)
    {
        return;
    }

    if(m_nCurIndex >= 0 && m_nCurIndex < size)
    {
        m_listWidgets[m_nCurIndex]->hide();
    }

    m_nCurIndex = 0;
    m_listWidgets[0]->show();
}

void PageManager::ShowPrePage()
{
    if(m_nCurIndex <= 0)
    {
        return;
    }

    m_listWidgets[m_nCurIndex--]->hide();
    m_listWidgets[m_nCurIndex]->show();
}

void PageManager::ShowNextPage()
{
    int size = m_listWidgets.size();
    if(m_nCurIndex >= size - 1)
    {
        return;
    }

    m_listWidgets[m_nCurIndex++]->hide();
    m_listWidgets[m_nCurIndex]->show();
}
