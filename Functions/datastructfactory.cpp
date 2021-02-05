//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "datastructfactory.h"

DataStructFactory* DataStructFactory::instance = nullptr;
DataStructFactory* DataStructFactory::Instance()
{
    if(instance == nullptr)
    {
        return new DataStructFactory();
    }
    else
    {
        return instance;
    }
}

DataStructFactory::DataStructFactory(QObject *parent)
    : QObject(parent)
{
    struct NameToWidget
    {
        NameToWidget(const QString& name_, CreateFun fun_)
        {
            name = name_;
            fun = fun_;
        }

        QString name;
        CreateFun fun;
    };

    struct NameToWidget arrNameToWidget[] =
    {
        NameToWidget("数组", &DataStructFactory::CreateArray),
        NameToWidget("链表", &DataStructFactory::CreateList),
        NameToWidget("栈", &DataStructFactory::CreateStack),
        NameToWidget("队列", &DataStructFactory::CreateQueue),
        NameToWidget("堆", &DataStructFactory::CreateHeap),

        NameToWidget("优先队列", &DataStructFactory::CreatePriorityQueue),
        NameToWidget("哈希表", &DataStructFactory::CreateHashTable),
        NameToWidget("二叉树", &DataStructFactory::CreateBinaryTree),
        NameToWidget("二叉搜索树", &DataStructFactory::CreateBinarySearchTree),
        NameToWidget("红黑树", &DataStructFactory::CreateRedBlackTree),

        NameToWidget("BTree", &DataStructFactory::CreateBTree),
        NameToWidget("BPlusTree", &DataStructFactory::CreateBPlusTree),
        NameToWidget("Graph", &DataStructFactory::CreateGraph),
    };

    int len = sizeof(arrNameToWidget) / sizeof(struct NameToWidget);
    for(int i = 0; i < len; i++)
    {
        mapCreateFun[arrNameToWidget[i].name] = arrNameToWidget[i].fun;
    }
}

QWidget* DataStructFactory::GetDataStructWidget(QString name, QWidget* parent)
{
    DataStructKey key(name, parent);
    if (mapWidget.contains(key))
    {
        return mapWidget.value(key);
    }
    else
    {
        if(mapCreateFun.contains(name))
        {
            CreateFun fun = mapCreateFun[name];
            QWidget* pWidget = fun(this, parent);
            mapWidget[DataStructKey(name, parent)] = pWidget;
            return pWidget;
        }
        else
        {
            return nullptr;
        }
    }
}

DataStructFactory::~DataStructFactory()
{
    QMap<DataStructKey, QWidget*>::iterator i;
    for (i = mapWidget.begin(); i != mapWidget.end(); ++i)
    {
        DataStructKey key = i.key();
        if(key.getParent() == nullptr)
        {
            delete i.value();
            // for effective and the factor mapWidget will destroy next, this step can jump over
            // mapWidget[key] = nullptr;
        }
    }
}

QWidget* DataStructFactory::CreateArray(QWidget* pParent)
{
    return new ArrayWidget(pParent);
}

QWidget* DataStructFactory::CreateList(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateStack(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateQueue(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateHeap(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreatePriorityQueue(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateHashTable(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateBinaryTree(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateBinarySearchTree(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateRedBlackTree(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateBTree(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateBPlusTree(QWidget* pParent)
{
    return new QWidget(pParent);
}

QWidget* DataStructFactory::CreateGraph(QWidget* pParent)
{
    return new QWidget(pParent);
}
