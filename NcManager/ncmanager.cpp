//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "ncmanager.h"

namespace NNcManager
{
    NcManager* NcManager::m_instance = nullptr;
    NcManager* NcManager::Instance()
    {
        if(m_instance == nullptr)
        {
            m_instance = new NcManager();
        }

        return m_instance;
    }

    NcManager::NcManager(QObject *parent) : QObject(parent)
    {
        m_pArrayNcGen = nullptr;
        //m_pArrayParse = nullptr;
    }

    QString NcManager::GetGeneralArrayDeleteFile(int nIndex_)
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_NC_PATH;
        bool _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
            _nDir.mkpath(_str);
        }

        _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
           assert(false);
        }

        _str += "/";
        _str += QString::asprintf("ArrayDelete_%d.nc", nIndex_);
        return _str;
    }

    QString NcManager::GetGeneralPraticalArrayDeleteFile(int nIndex_)
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_NC_PATH;
        bool _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
            _nDir.mkpath(_str);
        }

        _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
           assert(false);
        }

        _str += "/";
        _str += QString::asprintf("PraticalArrayDelete_%d.nc", nIndex_);
        return _str;
    }

    QString NcManager::GetGeneralPraticalArrayInsertFile(char* pContent_, int nIndex_)
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_NC_PATH;
        bool _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
            _nDir.mkpath(_str);
        }

        _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
           assert(false);
        }

        _str += "/";
        _str += QString::asprintf("PraticalArrayInsert_%s_%d.nc", pContent_, nIndex_);
        return _str;
    }

    QString NcManager::GetGeneralArrayInsertFile(char* pContent_, int nIndex_)
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_NC_PATH;
        bool _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
            _nDir.mkpath(_str);
        }

        _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
           assert(false);
        }

        _str += "/";
        _str += QString::asprintf("ArrayInsert_%s_%d.nc", pContent_, nIndex_);
        return _str;
    }

    QString NcManager::GetGeneralPraticalArraySearchFile(char* pContent_)
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_NC_PATH;
        bool _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
            _nDir.mkpath(_str);
        }

        _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
           assert(false);
        }

        _str += "/";
        _str += QString::asprintf("PraticalArraySearch_%s.nc", pContent_);
        return _str;
    }

    QString NcManager::GetGeneralArraySearchFile(char* pContent_)
    {
        QDir _nDir;
        QString _str = QApplication::applicationDirPath();
        _str += "/";
        _str += GENERAL_NC_PATH;
        bool _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
            _nDir.mkpath(_str);
        }

        _bExist = _nDir.exists(_str);
        if(!_bExist)
        {
           assert(false);
        }

        _str += "/";
        _str += QString::asprintf("ArraySearch_%s.nc", pContent_);
        return _str;
    }

    void NcManager::GeneralPraticalArrayInsertFileGenerate(
            char* pContent_,
            int nIndex_,
            double nDeltaLength_,
            NParameter::ArrayNcParameter nParam_,
            long nInsertObjId_)
    {
        if(m_pArrayNcGen == nullptr)
        {
            m_pArrayNcGen = new NFileGenerate::ArrayNcFileGenerate(this);
        }

        QString _str = GetGeneralPraticalArrayInsertFile(pContent_, nIndex_);
        m_pArrayNcGen->SetParameter(nParam_);
        m_pArrayNcGen->GenerateForInsert(
            _str,
            pContent_,
            nIndex_,
            nDeltaLength_,
            nInsertObjId_);
    }

    void NcManager::GeneralArrayInsertFileGenerate(
            char* pContent_,
            int nIndex_,
            double nDeltaLength_,
            NParameter::ArrayNcParameter nParam_,
            long nInsertObjId_)
    {
        if(m_pArrayNcGen == nullptr)
        {
            m_pArrayNcGen = new NFileGenerate::ArrayNcFileGenerate(this);
        }

        QString _str = GetGeneralArrayInsertFile(pContent_, nIndex_);
        m_pArrayNcGen->SetParameter(nParam_);
        m_pArrayNcGen->GenerateForInsert(
            _str,
            pContent_,
            nIndex_,
            nDeltaLength_,
            nInsertObjId_);
    }

    void NcManager::GeneralPraticalArrayDeleteFileGenerate(
            int nIndex_,
            double nDeltaLength_,
            NParameter::ArrayNcParameter nParam_)
    {
        if(m_pArrayNcGen == nullptr)
        {
            m_pArrayNcGen = new NFileGenerate::ArrayNcFileGenerate(this);
        }

        QString _str = GetGeneralPraticalArrayDeleteFile(nIndex_);
        m_pArrayNcGen->SetParameter(nParam_);
        m_pArrayNcGen->GenerateForDelete(
            _str,
            nIndex_,
            nDeltaLength_);
    }

    void NcManager::GeneralArrayDeleteFileGenerate(
            int nIndex_,
            double nDeltaLength_,
            NParameter::ArrayNcParameter nParam_)
    {
        if(m_pArrayNcGen == nullptr)
        {
            m_pArrayNcGen = new NFileGenerate::ArrayNcFileGenerate(this);
        }

        QString _str = GetGeneralArrayDeleteFile(nIndex_);
        m_pArrayNcGen->SetParameter(nParam_);
        m_pArrayNcGen->GenerateForDelete(
            _str,
            nIndex_,
            nDeltaLength_);
    }

    void NcManager::GeneralPraticalArraySearchFileGenerate(
            char* pContent_,
            NParameter::ArrayNcParameter nParam_)
    {
        if(m_pArrayNcGen == nullptr)
        {
            m_pArrayNcGen = new NFileGenerate::ArrayNcFileGenerate(this);
        }

        QString _str = GetGeneralPraticalArraySearchFile(pContent_);
        m_pArrayNcGen->SetParameter(nParam_);
        m_pArrayNcGen->GenerateForSearch(_str, pContent_);
    }

    void NcManager::GeneralArraySearchFileGenerate(
            char* pContent_,
            NParameter::ArrayNcParameter nParam_)
    {
        if(m_pArrayNcGen == nullptr)
        {
            m_pArrayNcGen = new NFileGenerate::ArrayNcFileGenerate(this);
        }

        QString _str = GetGeneralArraySearchFile(pContent_);
        m_pArrayNcGen->SetParameter(nParam_);
        m_pArrayNcGen->GenerateForSearch(_str, pContent_);
    }

    void NcManager::ArrayGenerateForInsert(
            int nIndex_,
            char* pContent_,
            NParameter::ArrayNcParameter nParam_)
    {

    }

    void NcManager::ArrayGenerateForDelete(
            int nIndex_,
            NParameter::ArrayNcParameter nParam_)
    {

    }
}
