//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FUNCTIONS_DATASTRUCTFACTORY_H
#define FUNCTIONS_DATASTRUCTFACTORY_H
#include "header.h"

class DataStructFactory;
using CreateFun = std::function<QWidget*(DataStructFactory*, QWidget*)>;

class DataStructKey
{
public:
    DataStructKey()
    {
        parentWidget = nullptr;
    }

    DataStructKey(QString name, QWidget* parent)
        :nameInfo(name)
    {
        parentWidget = parent;
    }

    bool operator==(const DataStructKey &key) const Q_DECL_NOTHROW
    {
        if(nameInfo == key.nameInfo && parentWidget == key.parentWidget)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator<(const DataStructKey &key) const Q_DECL_NOTHROW
    {
        if(nameInfo < key.nameInfo)
        {
            return true;
        }
        else if(nameInfo == key.nameInfo)
        {
            qulonglong ll1 = (qulonglong)parentWidget;
            qulonglong ll2 = (qulonglong)key.parentWidget;
            if(ll1 < ll2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    bool operator>(const DataStructKey &key) const Q_DECL_NOTHROW
    {
        return key.operator<(*this);
    }

    bool operator!=(const DataStructKey &key) const Q_DECL_NOTHROW
    {
        return !(this->operator==(key));
    }

    bool operator<=(const DataStructKey &key) const Q_DECL_NOTHROW
    {
        return !(this->operator>(key));
    }

    bool operator>=(const DataStructKey &key) const Q_DECL_NOTHROW
    {
        return !(this->operator<(key));
    }


    QWidget* getParent()
    {
        return parentWidget;
    }

    QString getName()
    {
        return nameInfo;
    }

private:
    QString nameInfo;
    QWidget* parentWidget;
};

class DataStructFactory : public QObject
{
    Q_OBJECT
public:
    static DataStructFactory* Instance();
    virtual ~DataStructFactory();
    QWidget* GetDataStructWidget(QString name, QWidget* parent);
protected:
    explicit DataStructFactory(QObject *parent = nullptr);


private:
    virtual QWidget* CreateArray(QWidget* parent);
    virtual QWidget* CreateList(QWidget* parent);
    virtual QWidget* CreateStack(QWidget* parent);
    virtual QWidget* CreateQueue(QWidget* parent);
    virtual QWidget* CreateHeap(QWidget* parent);
    virtual QWidget* CreatePriorityQueue(QWidget* parent);
    virtual QWidget* CreateHashTable(QWidget* parent);
    virtual QWidget* CreateBinaryTree(QWidget* parent);
    virtual QWidget* CreateBinarySearchTree(QWidget* parent);
    virtual QWidget* CreateRedBlackTree(QWidget* parent);
    virtual QWidget* CreateBTree(QWidget* parent);
    virtual QWidget* CreateBPlusTree(QWidget* parent);
    virtual QWidget* CreateGraph(QWidget* parent);

private:
    static DataStructFactory* instance;
    QMap<DataStructKey, QWidget*> mapWidget;
    QMap<QString, CreateFun> mapCreateFun;

};

#endif // DATASTRUCTFACTORY_H
