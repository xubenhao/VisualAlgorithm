//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_GENERATE_FILEGENERATE_H
#define FILE_GENERATE_FILEGENERATE_H
#include "header.h"

namespace NFileGenerate
{
    class FileGenerate : public QObject
    {
        Q_OBJECT
    public:
        explicit FileGenerate(QObject *parent = nullptr);
        virtual int Generate(const QString& filePath_);

        QFile m_file;
    };
}


#endif // FILEGENERATE_H
