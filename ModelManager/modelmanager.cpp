//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "modelmanager.h"

namespace NModelManager
{
    QString ModelManager::GetGeneralArrayModelFilePath()
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_MODEL_PATH;
        _str += "/";
        _str += GENERAL_ARRAY_MODEL_NAME;
        return _str;
    }

    QString ModelManager::GetPraticalArrayModelFilePath(
        int nId_,
        int nCapacity_)
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_MODEL_PATH;
        _str += "/";
        _str += QString::asprintf("Pratical_Arrar_%d_%d.xaml", nId_, nCapacity_);
        return _str;
    }

    ModelManager* ModelManager::m_instance = nullptr;
    ModelManager* ModelManager::Instance()
    {
        if(m_instance == nullptr)
        {
            m_instance = new ModelManager();
        }

        return m_instance;
    }

    ModelManager::ModelManager(QObject *parent) : QObject(parent)
    {
        m_pArrayGen = nullptr;
        m_pArrayParse = nullptr;
    }

    void ModelManager::GeneralPraticalArrayModelGenerate(
            QString strPath_,
            int nCapacity_)
    {
        if(m_pArrayGen == nullptr)
        {
            m_pArrayGen = new NFileGenerate::ArrayModelFileGenerate(this);
        }

        NParameter::ArrayParameter _nParam;
        NParameter::ArrayParameter::GetPraticalParameter(nCapacity_, _nParam);
        m_pArrayGen->SetParameter(_nParam);
        m_pArrayGen->Generate(strPath_);
    }

    void ModelManager::GeneralArrayModelGenerate()
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_MODEL_PATH;
        bool _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
            _nDir.mkpath(_str);
        }

        _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
           return;
        }

        _str += "/";
        _str += GENERAL_ARRAY_MODEL_NAME;
        if(m_pArrayGen == nullptr)
        {
            m_pArrayGen = new NFileGenerate::ArrayModelFileGenerate(this);
        }

        NParameter::ArrayParameter* _pParam = NParameter::ArrayParameter::GetGeneralParameter();
        m_pArrayGen->SetParameter(*_pParam);
        m_pArrayGen->Generate(_str);
    }

    NFileParse::FILE_PARSE_RET_CODE ModelManager::ArrayModelParse(
            const QString& strFilePath,
            NDataStruct::DynArray<NModel::Part*>& arrEleDyn_,
            NDataStruct::DynArray<NModel::Part*>& arrEleBackGroundDyn_,
            NDataStruct::DynArray<NModel::Part*>& arrEleAddrDyn_,
            NDataStruct::DynArray<NModel::Part*>& arrEleIndexDyn_)
    {
        if(m_pArrayParse == nullptr)
        {
            m_pArrayParse = new NFileParse::ArrayModelFileParse(this);
        }

        //NDataStruct::DynArray<NModel::Part*> _arrDynArr;
        NFileParse::FILE_PARSE_RET_CODE _nRet = m_pArrayParse->Parse(
                    strFilePath,
                    arrEleDyn_,
                    arrEleBackGroundDyn_,
                    arrEleAddrDyn_,
                    arrEleIndexDyn_);
        return _nRet;
    }
}

