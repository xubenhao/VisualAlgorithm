//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "transformgroup.h"

namespace NTransform
{
    TransformGroup::TransformGroup(QObject* parent)
        : Transform(parent)
    {

    }

    NMatrix::Matrix TransformGroup::GetMatrix()
    {
        NMatrix::Matrix _mxRet;
        int _nSize = m_arrTransforms.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            if(m_arrTransforms[_nSize - i - 1])
            {
                Transform* _pTrans = m_arrTransforms[_nSize - i - 1];
                NMatrix::Matrix _mxTempRet = _pTrans->GetMatrix();
                _mxRet = _mxRet.operator*(_mxTempRet);
            }
        }

        return _mxRet;
    }

    TransformGroup::~TransformGroup()
    {
    }

    void TransformGroup::Add(Transform* pTrans_)
    {
        m_arrTransforms.Add(pTrans_);
    }

    Transform* TransformGroup::DeepCopy()
    {
        TransformGroup* _pGroup = new TransformGroup();
        int _nSize = m_arrTransforms.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            Transform* _pTrans = m_arrTransforms[i]->DeepCopy();
            _pGroup->m_arrTransforms.Add(_pTrans);
            _pTrans->setParent(_pGroup);
        }

        return _pGroup;
    }

    void TransformGroup::PrintDebugInfo()
    {
        int _nSize = m_arrTransforms.GetSize();
        qDebug("this it TransformGroup Start\n");
        for(int i = 0; i < _nSize; i++)
        {
            Transform* _pTrans = m_arrTransforms[i];
            _pTrans->PrintDebugInfo();
        }

        qDebug("this it TransformGroup End\n");
    }

    void TransformGroup::PrintDebugInfo(QFile& hFile_)
    {
        int _nSize = m_arrTransforms.GetSize();
        QString _str = QString::asprintf(
                    "This it transformGroup start\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();

        for(int i = 0; i < _nSize; i++)
        {
            Transform* _pTrans = m_arrTransforms[i];
            _pTrans->PrintDebugInfo(hFile_);
        }
    }
}

