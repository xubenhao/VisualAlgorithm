//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "ncstepmove.h"

namespace NNcStep
{
    bool operator==(const MoveObj& nObj1_, const MoveObj& nObj2_)
    {
        //if(strcmp(nObj1_.m_strObjName, nObj2_.m_strObjName) == 0
        //    && nObj1_.m_nLengthDelta == nObj2_.m_nLengthDelta)
        if(nObj1_.m_nObjectId == nObj2_.m_nObjectId)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator!=(const MoveObj& nObj1_, const MoveObj& nObj2_)
    {
        return !operator==(nObj1_, nObj2_);
    }

    NcStepMove::NcStepMove(QObject *parent)
        : NcStep(parent)
    {
        m_nCurTimes = 0;
    }

    NcStep* NcStepMove::DeepCopy()
    {
        NcStepMove* _pStep = new NcStepMove();
        _pStep->m_arrMoveObjs = m_arrMoveObjs;
        _pStep->m_nCurTimes = m_nCurTimes;
        return _pStep;
    }

    void NcStepMove::GetNcShowPrepare()
    {
        m_nCurTimes = 0;
    }

    NNcShow::NcShow* NcStepMove::GetNcShow(
            QWidget* pWidget_,
            NDataStruct::DynArray<NModel::Part*>& arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
            NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_)
    {
        // change part's position
        // 1.we need to find out the part object according to its name
        // 2.then we need to change its curposition property according to its cur-position and the delta of its position
        // 3.then we do a redraw for all part according to their current position and color ...
        // 4.we thus get a image and put it into the ncshow buffer

        // one more thing here is
        // we show keep consuming the IndexPosStep one by one
        // until the consumed number reachs s_nSimuStepLength
        // or we meet other type ncstep
        // or we read to the end
        int _nCurTimes = 0;
        NDataStruct::DynArray<MoveObj> _arrMoveObjs;
        while(_nCurTimes++ < s_nSimuStepLength)
        {
            if(_nCurTimes == 1)
            {
                _arrMoveObjs = m_arrMoveObjs;
                // let this take effective
                for(int i = 0; i < m_arrMoveObjs.GetSize(); i++)
                {
                    // From Id To Part*
                    NModel::Part* _pPart = nullptr;
                    bool _bFlag = nKeyAllocator_.Find(m_arrMoveObjs[i].GetObjectId(), _pPart);
                    assert(_bFlag);
                    if(_pPart
                        && (_pPart->GetType() == NModel::MODEL_TYPE::MODEL_MOVABLEPART
                            || _pPart->GetType() == NModel::MODEL_TYPE::MODEL_APP_ARRAYPART))
                    {
                        NModel::MovablePart* _pMPart =  (NModel::MovablePart*)_pPart;
                        _pMPart->Delta(m_arrMoveObjs[i].m_nLengthDelta);

                    }

                    /*int j = 0;
                    for(; j < arrParts_.GetSize(); j++)
                    {
                        //if(strcmp(m_arrMoveObjs[i].m_strObjName, arrParts_[j]->GetName()) == 0)
                        if(m_arrMoveObjs[i].GetObjectId(), arrParts_[j]->GetObjectId())
                        {
                            // Just For Debug
                            char _name1[100];
                            char _name2[200];
                            memset(_name1, 0, sizeof(_name1));
                            memset(_name2, 0, sizeof(_name2));
                            strncpy(_name1, m_arrMoveObjs[i].m_strObjName, sizeof(_name1));
                            strncpy(_name2, arrParts_[j]->GetName(), sizeof(_name2));
                            break;
                        }
                    }

                    if(j >= arrParts_.GetSize()
                        || (arrParts_[j]->GetType() != NModel::MODEL_TYPE::MODEL_MOVABLEPART
                            && arrParts_[j]->GetType() != NModel::MODEL_TYPE::MODEL_APP_ARRAYPART))
                    {
                        assert(false);
                    }
                    else
                    {
                        NModel::MovablePart* _pPart =  (NModel::MovablePart*)arrParts_[j];
                        _pPart->Delta(m_arrMoveObjs[i].m_nLengthDelta);
                    }*/
                }
            }

            NcStep* _pStep;
            int _nRet = pNcStepBuffer_->Peek(_pStep);
            // End
            if(_nRet != 1)
            {
                break;
            }

            if(_pStep->GetType() != NCSTEP_TYPE::_MOVE)
            {
                break;
            }

            NcStepMove* _pMove = (NcStepMove*)_pStep;
            bool _bContinue = true;
            for(int i = 0; i < _pMove->m_arrMoveObjs.GetSize(); i++)
            {
                // From Id To Part*
                //NModel::Part* _pPart = nullptr;
                //nKeyAllocator_.Find(_pMove->m_arrMoveObjs[i].GetObjectId(), _pPart);

                int j = 0;
                for(; j < _arrMoveObjs.GetSize(); j++)
                {
                    if(_arrMoveObjs[j].GetObjectId() == _pMove->m_arrMoveObjs[i].GetObjectId())
                    //if(strcmp(_arrMoveObjs[i].m_strObjName,
                    //          _pMove->m_arrMoveObjs[i].m_strObjName) == 0)
                    {
                        break;
                    }
                }

                if(j >= _arrMoveObjs.GetSize()
                    || _pMove->m_arrMoveObjs[i].m_nLengthDelta * _arrMoveObjs[j].m_nLengthDelta < 0)
                {
                    _bContinue = false;
                    break;
                }
            }

            if(_bContinue == false)
            {
                break;
            }

            // let _pMove take effective
            pNcStepBuffer_->Pop(_pStep);
            _pMove = (NcStepMove*)_pStep;
            // let this take effective
            for(int i = 0; i < _pMove->m_arrMoveObjs.GetSize(); i++)
            {
                // From Id To Part*
                NModel::Part* _pPart = nullptr;
                bool _bFlag = nKeyAllocator_.Find(_pMove->m_arrMoveObjs[i].GetObjectId(), _pPart);
                assert(_bFlag);
                if(_pPart
                    && (_pPart->GetType() == NModel::MODEL_TYPE::MODEL_MOVABLEPART
                        || _pPart->GetType() == NModel::MODEL_TYPE::MODEL_APP_ARRAYPART))
                {
                    NModel::MovablePart* _pMPart =  (NModel::MovablePart*)_pPart;
                    _pMPart->Delta(_pMove->m_arrMoveObjs[i].m_nLengthDelta);
                }
                /*int j = 0;
                for(; j < arrParts_.GetSize(); j++)
                {
                    //if(strcmp(_pMove->m_arrMoveObjs[i].m_strObjName, arrParts_[j]->GetName()) == 0)
                    if(_pMove->m_arrMoveObjs[i].GetObjectId() == arrParts_[j]->GetObjectId())
                    {
                        break;
                    }
                }

                if(j >= arrParts_.GetSize()
                    || (arrParts_[j]->GetType() != NModel::MODEL_TYPE::MODEL_MOVABLEPART
                        && arrParts_[j]->GetType() != NModel::MODEL_TYPE::MODEL_APP_ARRAYPART))
                {
                    assert(false);
                }
                else
                {
                    NModel::MovablePart* _pPart =  (NModel::MovablePart*)arrParts_[j];
                    _pPart->Delta(_pMove->m_arrMoveObjs[i].m_nLengthDelta);
                }*/
            }

            delete _pStep;
        }

        // draw image
        QImage image = QImage(pWidget_->size(), QImage::Format_RGB32);
        image.fill(Qt::white);

        int _nSize = arrParts_.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            arrParts_[i]->Draw(&image);
        }

        NNcShow::NcShowImage* _pImage = new NNcShow::NcShowImage();
        _pImage->SetImage(image);
        return _pImage;
    }
}
