//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_PARSE_FILEPARSE_H
#define FILE_PARSE_FILEPARSE_H

#include "header.h"

namespace NFileParse
{
    class FileParse : public QObject
    {
        Q_OBJECT
    public:
        explicit FileParse(QObject *parent = nullptr);


    protected:
        QFile m_file;
    };
}


#endif // FILEPARSE_H
