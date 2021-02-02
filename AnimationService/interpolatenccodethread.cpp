//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "interpolatenccodethread.h"

namespace NAnimationService
{
    InterpolateNcCodeThread::InterpolateNcCodeThread(
        const NParameter::ArrayNcParameter& arrParam_,
        const NFileParse::ArrayModalData& arrModalData_,
        NSync::FixBufferFor1P1C<NNcCode::NcCode*, 100>* pNcCodeBuffer_,
        NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_,
        QObject* pParent_)
        : QThread(pParent_)
    {
        m_nParam = arrParam_;
        m_nModalData = arrModalData_;
        m_pNcCodeBuffer = pNcCodeBuffer_;
        m_pNcStepBuffer = pNcStepBuffer_;
        m_bStop = false;
        m_nState = PRODUCER_NOT_START;
    }

    InterpolateNcCodeThread::~InterpolateNcCodeThread()
    {

    }

    THREAD_STATE InterpolateNcCodeThread::GetThreadState()
    {
        if(m_nState == PRODUCER_NOT_START)
        {
            return THREAD_NOT_START;
        }
        else if(m_nState == PRODUCER_RUNNING)
        {
            return THREAD_RUNNING;
        }
        else if(m_nState == PRODUCER_PAUSED)
        {
            return THREAD_PAUSED;
        }
        else if(m_nState == PRODUCER_NORMAL_END)
        {
            return THREAD_NORMALLY_END;
        }
        else
        {
            return THREAD_ABNORMALLY_END;
        }
    }

    void InterpolateNcCodeThread::Stop()
    {
        m_bStop = true;
    }

    void WriteNcStepTip(QFile& file_, NNcStep::NcStepTip* pNcStep_)
    {
        QString _str = QString::asprintf(
                    "NcTip:%s\n",
                    pNcStep_->GetTip());
        QByteArray _nByteArr = _str.toUtf8();
        file_.write(_nByteArr);
        file_.flush();
    }

    void WriteNcStepControl(QFile& file_, NNcStep::NcStepControl* pNcStep_)
    {
        QString _str = QString::asprintf(
                    "NcStepControl:%d\n",
                    pNcStep_->GetEnableRefresh());
        QByteArray _nByteArr = _str.toUtf8();
        file_.write(_nByteArr);
        file_.flush();
    }

    void WriteNcStepColor(QFile& file_, NNcStep::NcStepColor* pNcStep_)
    {
        for(int i = 0; i < pNcStep_->GetColorObjSize(); i++)
        {
            ColorObj _nObj = pNcStep_->GetColorObj(i);
            QString _str = QString::asprintf(
                        "NcStepColor:Name=%s,Color_R=%d,Color_G=%d,Color_B=%d,Color_A=%d\n",
                        _nObj.m_strObjName,
                        _nObj.m_nColor.m_nR,
                        _nObj.m_nColor.m_nG,
                        _nObj.m_nColor.m_nB,
                        _nObj.m_nColor.m_nA);
            QByteArray _nByteArr = _str.toUtf8();
            file_.write(_nByteArr);
            file_.flush();
        }
    }

    void WriteNcStepMove(QFile& file_, NNcStep::NcStepMove* pNcStep_)
    {
        for(int i = 0; i < pNcStep_->GetMoveObjSize(); i++)
        {
            NNcStep::MoveObj _nObj = pNcStep_->GetMoveObj(i);
            QString _str = QString::asprintf(
                        "NcStepMove:Name=%s,Delta=%.f\n",
                        _nObj.m_strObjName,
                        _nObj.m_nLengthDelta);
            QByteArray _nByteArr = _str.toUtf8();
            file_.write(_nByteArr);
            file_.flush();
        }
    }

    void WriteNcStep(QFile& file_, NNcStep::NcStep* pStep_)
    {
        NNcStep::NCSTEP_TYPE _nType = pStep_->GetType();
        if(_nType == NNcStep::NCSTEP_TYPE::_TIP)
        {
            WriteNcStepTip(file_, (NNcStep::NcStepTip*)pStep_);
        }

        if(_nType == NNcStep::NCSTEP_TYPE::_CONTROL)
        {
            WriteNcStepControl(file_, (NNcStep::NcStepControl*)pStep_);
        }

        if(_nType == NNcStep::NCSTEP_TYPE::_COLOR)
        {
            WriteNcStepColor(file_, (NNcStep::NcStepColor*)pStep_);
        }

        if(_nType == NNcStep::NCSTEP_TYPE::_MOVE)
        {
            WriteNcStepMove(file_, (NNcStep::NcStepMove*)pStep_);
        }
    }


    void InterpolateNcCodeThread::run()
    {
        m_nState = PRODUCER_RUNNING;

        // for debug
        // For Debug
        QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile(
                    (char*)"4_interpolate_test");
        QFile _file;
        _file.close();
        _file.setFileName(_filepath);
        bool _bRet = _file.open(
                    QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        if(!_bRet)
        {
            assert(false);
        }

        while(!m_bStop)
        {
            NNcCode::NcCode* _pNcCode = nullptr;
            // for NcCodeBuffer,We are consumer
            int _nRet = m_pNcCodeBuffer->Pop(_pNcCode);
            // consume a nc code
            if(_nRet == 1)
            {
                // ok
            }
            // meanning not have any more nc code to consume
            else if(_nRet == 0)
            {
                // as a producer this is the time we have complete the producing
                m_nState = PRODUCER_NORMAL_END;
                break;
            }
            // meaning the nocodebuffer's producer has abnormally-end
            // and we have not any more nccode to consumer
            // so as a producer
            // we stopped here,abnormally
            else
            {
                m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END;
                break;
            }

            if(_pNcCode)
            {
                _pNcCode->GetNcStepPrepare();
                while(true)
                {
                    NNcStep::NcStep* _pStep = _pNcCode->GetNcStep();
                    if(_pStep == nullptr)
                    {
                        break;
                    }

                    WriteNcStep(_file, _pStep);
                    int _nRetSyn = m_pNcStepBuffer->Push(_pStep);
                    if(_nRetSyn == 1)
                    {
                        // ok
                    }
                    // for ncstepbuffer we are producer
                    // if return 0,meaning the consumer has normally end
                    // this cannot be happend
                    else if(_nRetSyn == 0)
                    {
                        // this cannot be happend
                        assert(false);
                        m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END;
                        break;
                    }
                    // for ncstepbuffer we are producer
                    // if return -1,meaning the consumer has abnormally end
                    // so we need stop producing immediately
                    else
                    {
                        m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END;
                        break;
                    }
                }

                delete _pNcCode;
                _pNcCode = nullptr;
            }
            else
            {
                m_nState = PRODUCER_ABNORMAL_END_AS_UNEXPECTED;
                break;
            }

            if(m_nState != PRODUCER_RUNNING)
            {
                break;
            }
        }

        if(m_bStop)
        {
            m_nState = PRODUCER_ABNORMAL_END_SELF;
        }

        if(m_nState == PRODUCER_NORMAL_END)
        {
            m_pNcStepBuffer->SetProducerState(NSyn::OBJECT_STATE::NORMALLY_END);
        }

        if(m_nState == PRODUCER_ABNORMAL_END_SELF
            || m_nState == PRODUCER_ABNORMAL_END_AS_UNEXPECTED
            || m_nState == PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END
            || m_nState == PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END)
        {
            m_pNcStepBuffer->SetProducerState(NSyn::OBJECT_STATE::ABNORMALLY_END);
        }

    }
}

