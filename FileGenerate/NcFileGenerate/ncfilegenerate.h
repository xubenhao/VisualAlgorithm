//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_GENERATE_NCFILEGENERATE_H
#define FILE_GENERATE_NCFILEGENERATE_H

#include "FileGenerate/filegenerate.h"
namespace NFileGenerate
{
    class NcFileGenerate : public FileGenerate
    {
        Q_OBJECT
    public:
        explicit NcFileGenerate(QObject *parent = nullptr)
            :FileGenerate(parent)
        {};

    signals:

    };

}


#endif // NCFILEGENERATE_H
