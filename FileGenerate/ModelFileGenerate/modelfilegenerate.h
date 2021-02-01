//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_GENERATE_MODELFILEGENERATE_H
#define FILE_GENERATE_MODELFILEGENERATE_H

#include "FileGenerate/filegenerate.h"
namespace NFileGenerate
{
    class ModelFileGenerate : public FileGenerate
    {
        Q_OBJECT
    public:
        explicit ModelFileGenerate(QObject *parent = nullptr)
            : FileGenerate(parent)
        {};
        virtual int Generate(const QString& filePath_){Q_UNUSED(filePath_);return SUCCESS;};

    signals:

    };
}


#endif // MODELFILEGENERATE_H
