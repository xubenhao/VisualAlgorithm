//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "part.h"

namespace NModel
{
    Part::Part(QObject* parent)
        : QObject(parent)
    {
        m_pInitialTransform = nullptr;
        m_pDrawing = nullptr;
        m_pParent = nullptr;
        strncpy(m_strName, "", sizeof(m_strName));
        m_nObjectID = -1;
    }

    Part::~Part()
    {

    }

    NTransform::Transform* Part::GetTransform()
    {
        if(m_pInitialTransform)
        {
            return m_pInitialTransform->DeepCopy();
        }
        else
        {
            return new NTransform::LinearTransform();
        }

    }

    Part* Part::GetParent()
    {
        return m_pParent;
    }

    void Part::Draw(QImage* pImage_)
    {
        if(m_pDrawing)
        {
            // 1.get accumulate transform 
            // from all parent
            NTransform::TransformGroup* _pTransGroup
                = new NTransform::TransformGroup();
            NTransform::Transform* _pTrans 
                = GetTransform();
            _pTrans->PrintDebugInfo();
            _pTrans->setParent(_pTransGroup);
            _pTransGroup->Add(_pTrans);
            Part* _pParent = GetParent();
            while(_pParent)
            {
                _pTrans = _pParent->GetTransform();
                _pTrans->setParent(_pTransGroup);
                _pTransGroup->Add(_pTrans);
                _pParent = _pParent->GetParent();
            }


            // 2.draw self with right transform
            _pTransGroup->PrintDebugInfo();

            // every part's position 
            // and the translatings 
            // we discussed all based 
            // on logic coordinate
            // to see the show coordinate 
            // with the show in logic coordinate
            // before draw 
            // we add a logic to scree transform 
            // for every part
            double _nMx[3][3] =
            {
                {1.0, 0.0 ,1.0},
                {0.0, -1.0, 1.0},
                {0.0, 0.0, 1.0},
            };

            NMatrix::Matrix _mxM(_nMx);
            NTransform::MatrixTransform *_pMxTrans 
                = new NTransform::MatrixTransform(_mxM, _pTransGroup);
            _pTransGroup->Add(_pMxTrans);
            m_pDrawing->Draw(_pTransGroup, pImage_);
            delete _pTransGroup;
        }


        // 3.let all child to draw
        int _nSize = m_arrChilds.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            m_arrChilds[i]->Draw(pImage_);
        }
    }

    void Part::SetName(char (&strName_)[100])
    {
        strncpy(m_strName, strName_, sizeof (m_strName));
    }

    void Part::SetName(const QByteArray& nByteArr_)
    {
        strncpy(m_strName, nByteArr_.data(), sizeof (m_strName));
    }

    void Part::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "Part's Name:%s\n",
                    m_strName);
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();

        _str = QString::asprintf(
                    "Part's ObjectId:%ld\n",
                    m_nObjectID);
        _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();

        _str = QString::asprintf(
                    "Part's InitialTransform\n");
        _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();
        m_pInitialTransform->PrintDebugInfo(hFile_);

        m_pDrawing->OutputDebugInfo(hFile_);
        for(int i = 0; i < m_arrChilds.GetSize(); i++)
        {
            m_arrChilds[i]->OutputDebugInfo(hFile_);
        }
    }
}

