//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_GENERATE_ARRAYMODELFILEGENERATE_H
#define FILE_GENERATE_ARRAYMODELFILEGENERATE_H

#include "modelfilegenerate.h"

namespace NFileGenerate
{
    class ArrayModelFileGenerate : public ModelFileGenerate
    {
    public:
        ArrayModelFileGenerate(QObject* object = nullptr);
        void SetParameter(const NParameter::ArrayParameter& nParam_){m_nParam = nParam_;}
        int Generate(const QString& filePath_);


    private:
        void WriteArrayModel(int nFlag_);
        void WriteArray(int nFlag_);
        void WriteElement(const NParameter::Element& nElement_);
        void WriteElementAddress(const NParameter::ElementAddress& nElementAddress_);
        void WriteElementIndex(const NParameter::ElementIndex& nElementIndex_);

    private:
        NParameter::ArrayParameter m_nParam;
    };
}


#endif // ARRAYMODELFILEGENERATE_H
