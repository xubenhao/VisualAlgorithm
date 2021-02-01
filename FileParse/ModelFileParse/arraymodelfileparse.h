//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef FILE_PARSE_ARRAYMODELFILEPARSE_H
#define FILE_PARSE_ARRAYMODELFILEPARSE_H
#include "modelfileparse.h"

namespace NFileParse
{
    class ArrayModelFileParse : public ModelFileParse
    {
    public:
        ArrayModelFileParse(QObject *parent = nullptr);
        virtual FILE_PARSE_RET_CODE Parse(
                const QString& strFilePath_,
                NDataStruct::DynArray<NModel::Part*>& dynEleArr_,
                NDataStruct::DynArray<NModel::Part*>& dynEleBackGroundArr_,
                NDataStruct::DynArray<NModel::Part*>& dynEleAddrArr_,
                NDataStruct::DynArray<NModel::Part*>& dynEleIndexArr_);

        virtual FILE_PARSE_RET_CODE ParseFile(
                const QString& strFilePath_,
                NParameter::ArrayParameter& nParam_);


        virtual FILE_PARSE_RET_CODE BuildModel(
                const NParameter::ArrayParameter& nParam_,
                NDataStruct::DynArray<NModel::Part*>& dynEleArr_,
                NDataStruct::DynArray<NModel::Part*>& dynEleBackGroundArr_,
                NDataStruct::DynArray<NModel::Part*>& dynEleAddrArr_,
                NDataStruct::DynArray<NModel::Part*>& dynEleIndexArr_);


    private:
        FILE_PARSE_RET_CODE ReadArrayModel(int nFlag_);
        FILE_PARSE_RET_CODE ReadArray(int nFlag_, NParameter::ArrayParameter& nParam_);
        FILE_PARSE_RET_CODE ReadElement(NParameter::Element& nEle_);
        FILE_PARSE_RET_CODE ReadElementAddress(NParameter::ElementAddress& nEleAddress_);
        FILE_PARSE_RET_CODE ReadElementIndex(NParameter::ElementIndex& nEleIndex_);
        FILE_PARSE_RET_CODE GetInt(
            const QByteArray& arrByte_,
            int nSIndex_,
            const char* strSep1_,
            const char* strSep2_,
            int& nRet_);
        FILE_PARSE_RET_CODE GetDouble(
            const QByteArray& arrByte_,
            int nSIndex_,
            const char* strSep1_,
            const char* strSep2_,
            double& nRet_);
        FILE_PARSE_RET_CODE GetString(
            const QByteArray& arrByte_,
            int nSIndex_,
            const char* strSep1_,
            const char* strSep2_,
            QByteArray& nStr_);


        void ConstuctElementParts(
                const NParameter::ArrayParameter& nParam_,
                NDataStruct::DynArray<NModel::Part*>& dynArr_,
                NDataStruct::DynArray<NModel::Part*>& dynBackGroundArr_);
        void ConstuctElementAddressParts(
                const NParameter::ArrayParameter& nParam_,
                NDataStruct::DynArray<NModel::Part*>& dynArr_);
        void ConstuctElementIndexParts(
                const NParameter::ArrayParameter& nParam_,
                NDataStruct::DynArray<NModel::Part*>& dynArr_);
    };
}


#endif // ARRAYMODELFILEPARSE_H
