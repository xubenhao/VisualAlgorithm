//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef MODEL_MANAGER_MODELMANAGER_H
#define MODEL_MANAGER_MODELMANAGER_H
#include "header.h"

namespace NModelManager
{
    class ModelManager : public QObject
    {
        Q_OBJECT
    public:
        static QString GetGeneralArrayModelFilePath();
        static QString GetPraticalArrayModelFilePath(
            int nId_,
            int nCapacity_);
        static QString GetPraticalArrayNcFilePath(
            int nId_,
            int nCapacity_);

        static ModelManager* Instance();
        void GeneralArrayModelGenerate();
        void GeneralPraticalArrayModelGenerate(
                QString strPath_,
                int nCapacity_);
        NFileParse::FILE_PARSE_RET_CODE ArrayModelParse(
                const QString& strFilePath,
                NDataStruct::DynArray<NModel::Part*>& arrEleDyn_,
                NDataStruct::DynArray<NModel::Part*>& arrEleBackGroundDyn_,
                NDataStruct::DynArray<NModel::Part*>& arrEleAddrDyn_,
                NDataStruct::DynArray<NModel::Part*>& arrEleIndexDyn_);

    protected:
        explicit ModelManager(QObject *parent = nullptr);
    private:
        NFileGenerate::ArrayModelFileGenerate* m_pArrayGen;
        NFileParse::ArrayModelFileParse* m_pArrayParse;
        static ModelManager* m_instance;
    };
}


#endif // MODELMANAGER_H
