//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_PARSE_NCFILEPARSE_H
#define FILE_PARSE_NCFILEPARSE_H

#include "FileParse/fileparse.h"
namespace NFileParse
{
    class NcFileParse : public FileParse
    {
    public:
        NcFileParse(QObject *parent = nullptr);
    };
}

#endif
