//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "filegenerate.h"

namespace NFileGenerate
{
    FileGenerate::FileGenerate(QObject *parent)
        : QObject(parent)
    {

    }

    int FileGenerate::Generate(const QString& filePath_)
    {
        return SUCCESS;
    }
}

