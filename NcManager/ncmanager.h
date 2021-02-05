//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NC_MANAGER_NCMANAGER_H
#define NC_MANAGER_NCMANAGER_H
#include "header.h"
namespace NNcManager
{
    class NcManager : public QObject
    {
        Q_OBJECT
    public:
        static NcManager* Instance();
        static QString GetGeneralArraySearchFile(char* pContent_);
        static QString GetGeneralArrayInsertFile(
                char* pContent_, 
                int nIndex_);
        static QString GetGeneralArrayDeleteFile(int nIndex_);

        static QString GetGeneralPraticalArraySearchFile(
                char* pContent_);
        static QString GetGeneralPraticalArrayInsertFile(
                char* pContent_, 
                int nIndex_);
        static QString GetGeneralPraticalArrayDeleteFile(
                int nIndex_);


        void GeneralPraticalArrayInsertFileGenerate(
                char* pContent_,
                int nIndex_,
                double nDeltaLength_,
                NParameter::ArrayNcParameter nParam_,
                long nInsertObjId_);


        void GeneralArraySearchFileGenerate(
                char* pContent_,
                NParameter::ArrayNcParameter nParam_);
        void GeneralPraticalArraySearchFileGenerate(
                char* pContent_,
                NParameter::ArrayNcParameter nParam_);



        void GeneralArrayInsertFileGenerate(
                char* pContent_,
                int nIndex_,
                double nDeltaLength_,
                NParameter::ArrayNcParameter nParam_,
                long nInsertObjId_);


        void GeneralPraticalArrayDeleteFileGenerate(
                int nIndex_,
                double nDeltaLength_,
                NParameter::ArrayNcParameter nParam_);

        void GeneralArrayDeleteFileGenerate(
                int nIndex_,
                double nDeltaLength_,
                NParameter::ArrayNcParameter nParam_);

        void ArrayGenerateForInsert(
                int nIndex_,
                char* pContent_,
                NParameter::ArrayNcParameter nParam_);
        void ArrayGenerateForDelete(
                int nIndex_,
                NParameter::ArrayNcParameter nParam_);
    protected:
        explicit NcManager(QObject *parent = nullptr);
    private:
        NFileGenerate::ArrayNcFileGenerate* m_pArrayNcGen;
        //NFileParse::ArrayModelFileParse* m_pArrayParse;
        static NcManager* m_instance;
    };
}


#endif // NCMANAGER_H
