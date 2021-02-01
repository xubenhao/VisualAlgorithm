//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_GENERATE_ARRAYNCFILEGENERATE_H
#define FILE_GENERATE_ARRAYNCFILEGENERATE_H
#include "ncfilegenerate.h"

namespace NFileGenerate
{
    class ArrayNcFileGenerate : public NcFileGenerate
    {
    public:
        ArrayNcFileGenerate(QObject* object = nullptr);
        void SetParameter(NParameter::ArrayNcParameter nParam_){m_nParam = nParam_;}
        int GenerateForSearch(
                const QString& filePath_,
                char* pContent_);
        int GenerateForInsert(
                const QString& filePath_,
                char* pContent_,
                int nIndex_,
                double nDeltaLength_,
                long nInsertObjId_);
        int GenerateForDelete(
                const QString& filePath_,
                int nIndex_,
                double nDeltaLength_);

    private:
        NParameter::ArrayNcParameter m_nParam;
    };
}


#endif // ARRAYNCFILEGENERATE_H
