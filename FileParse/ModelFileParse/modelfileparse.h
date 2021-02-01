//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_PARSE_MODELFILEPARSE_H
#define FILE_PARSE_MODELFILEPARSE_H

#include "FileParse/fileparse.h"

namespace NFileParse
{
    class ModelFileParse : public FileParse
    {
        Q_OBJECT
    public:
        explicit ModelFileParse(QObject *parent = nullptr);
        //virtual FILE_PARSE_RET_CODE Parse(const QString& strFilePath_, NDataStruct::DynArray<NModel::Part*>& dynArr_);
    };
}


#endif // MODELFILEPARSE_H
