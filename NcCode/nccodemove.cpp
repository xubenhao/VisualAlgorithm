//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "nccodemove.h"

namespace NNcCode
{
    bool operator==(const MoveObj& nObj1_, const MoveObj& nObj2_)
    {
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

    NcCodeMove::NcCodeMove(QObject *parent)
        : NcCode(parent)
    {
        m_nMoveType = MOVE_TYPE::LINEAR_MOVE;
        m_nCurTimes = 0;
        m_nTotalTimes = 0;
    }

    NcCode* NcCodeMove::DeepCopy()
    {
        NcCodeMove* _pCode = new NcCodeMove();
        _pCode->m_arrMoveObjs = m_arrMoveObjs;
        _pCode->m_nMoveType = m_nMoveType;
        _pCode->m_nTotalTimes = m_nTotalTimes;
        _pCode->m_nCurTimes = m_nCurTimes;
        return _pCode;
    }

    void NcCodeMove::GetNcStepPrepare()
    {
        m_nCurTimes = 0;
        // Calculate Time
        // MultiObj Move
        // The Speed
        // Every Object has his own Speed
        // But All Object must start from his start point at the same time
        // and reach his end point at the same time too
        // so oject in collection has relation in his speed with each other

        // every object has a speed and a length
        // thus,for every object there is a total time for move
        // we use the max time of all as every object's actual total time for move
        // thus,this cause a case that the should have reach early object,
        // now will slow his speed to reach his end point at the same time
        // with the object should latest reach if not we have not taken this strategy.
        double _nTotalTime = 0.0;
        for(int i = 0; i < m_arrMoveObjs.GetSize(); i++)
        {
            double _nTime = abs(m_arrMoveObjs[i].m_nLengthDelta) / NcCode::s_nFixInterpSpeed;
            if(_nTotalTime < _nTime)
            {
                _nTotalTime = _nTime;
            }
        }

        m_nTotalTimes = _nTotalTime / NcCode::s_nFixInterpInterval;
        for(int i = 0; i < m_arrMoveObjs.GetSize(); i++)
        {
            m_arrMoveObjs[i].m_nLengthDeltaOnInterval = m_arrMoveObjs[i].m_nLengthDelta * s_nFixInterpInterval / _nTotalTime;
        }
    }

    NNcStep::NcStep* NcCodeMove::GetNcStep()
    {
        int _nCurGetTimes = m_nCurTimes++;
        if(m_nMoveType == MOVE_TYPE::ONE_JUMP)
        {
            if(_nCurGetTimes == 0)
            {
                NNcStep::NcStepMove* _pStep = new NNcStep::NcStepMove();
                for(int i = 0; i < m_arrMoveObjs.GetSize(); i++)
                {
                    // Test
                    //double _nLen = m_arrMoveObjs[i].m_nLengthDelta;
                    NNcStep::MoveObj _nMoveObj(
                                m_arrMoveObjs[i].m_strObjName,
                                m_arrMoveObjs[i].m_nLengthDelta,
                                m_arrMoveObjs[i].GetObjectId());
                    _pStep->AddMoveObj(_nMoveObj);
                }

                return _pStep;
            }
            else if(_nCurGetTimes == 1)
            {
                return nullptr;
            }
            else
            {
                assert(false);
                return nullptr;
            }
        }


        // we know angle
        // we know length
        // if we accord to a fix interval, a fix speed
        // and assume that non acceleration involves in the move.
        // then we get a interp plan
        // logic position's unit is mm
        if(_nCurGetTimes < m_nTotalTimes)
        {
            NNcStep::NcStepMove* _pStep = new NNcStep::NcStepMove();
            for(int i = 0; i < m_arrMoveObjs.GetSize(); i++)
            {
                NNcStep::MoveObj _nMoveObj(
                            m_arrMoveObjs[i].m_strObjName,
                            m_arrMoveObjs[i].m_nLengthDeltaOnInterval,
                            m_arrMoveObjs[i].GetObjectId());
                _pStep->AddMoveObj(_nMoveObj);
            }

            return _pStep;
        }
        else if(_nCurGetTimes == m_nTotalTimes)
        {
            double _nRemainLength = 0.0;
            NNcStep::NcStepMove* _pStep = new NNcStep::NcStepMove();
            for(int i = 0; i < m_arrMoveObjs.GetSize(); i++)
            {
                double _nRemain = m_arrMoveObjs[i].m_nLengthDelta
                        - m_nTotalTimes * m_arrMoveObjs[i].m_nLengthDeltaOnInterval;
                NNcStep::MoveObj _nMoveObj(
                            m_arrMoveObjs[i].m_strObjName,
                            _nRemain,
                            m_arrMoveObjs[i].GetObjectId());
                if(_nRemainLength < _nRemain)
                {
                    _nRemainLength = _nRemain;
                }

                _pStep->AddMoveObj(_nMoveObj);
            }

            if(abs(_nRemainLength) < 0.000001)
            {
                delete  _pStep;
                return nullptr;
            }
            else
            {
                return _pStep;
            }
        }
        else if(_nCurGetTimes == m_nTotalTimes + 1)
        {
            double _nRemainLength = 0.0;
            for(int i = 0; i < m_arrMoveObjs.GetSize(); i++)
            {
                double _nRemain = m_arrMoveObjs[i].m_nLengthDelta
                        - m_nTotalTimes * m_arrMoveObjs[i].m_nLengthDeltaOnInterval;
                if(_nRemainLength < _nRemain)
                {
                    _nRemainLength = _nRemain;
                }
            }

            if(abs(_nRemainLength) <= 0.000001)
            {
                assert(false);
                return nullptr;
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            assert(false);
            return nullptr;
        }
    }
}

