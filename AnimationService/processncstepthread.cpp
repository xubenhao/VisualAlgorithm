//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "processncstepthread.h"

namespace NAnimationService
{
    ProcessNcStepThread::ProcessNcStepThread(
        //const NParameter::ArrayNcParameter& arrParam_,
        QWidget* pWidget_,
        NDataStruct::DynArray<NModel::Part*> arrParts_,
        NDataStruct::KeyAllocator<NModel::Part*> nKeyAllocator_,
        NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_,
        NSync::FixBufferFor1P1C<NNcShow::NcShow*, 20>* pNcShowBuffer_,
        QObject* pParent_)
        : QThread(pParent_)
    {
        //m_nParam = arrParam_;
        m_pWidget = pWidget_;
        m_arrParts = arrParts_;
        m_nKeyAllocator = nKeyAllocator_;
        //m_pNcCodeBuffer = pNcCodeBuffer_;
        m_pNcStepBuffer = pNcStepBuffer_;
        m_pNcShowBuffer = pNcShowBuffer_;
        m_bStop = false;
        m_nState = PRODUCER_NOT_START;
    }

    ProcessNcStepThread::~ProcessNcStepThread()
    {

    }

    void ProcessNcStepThread::Stop()
    {
        m_bStop = true;
    }

    THREAD_STATE ProcessNcStepThread::GetThreadState()
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

    void WriteNcShowTip(QFile& file_, NNcShow::NcShowTip* pShowTip_)
    {
        QString _str = QString::asprintf(
                    "NcShowTip:%s\n",
                    pShowTip_->GetTip());
        QByteArray _nByteArr = _str.toUtf8();
        file_.write(_nByteArr);
        file_.flush();
    }

    void WriteNcShowControl(QFile& file_, NNcShow::NcShowControl* pShowControl_)
    {
        QString _str = QString::asprintf(
                    "NcShowControl:%d\n",
                    pShowControl_->GetRefreshEnable());
        QByteArray _nByteArr = _str.toUtf8();
        file_.write(_nByteArr);
        file_.flush();
    }

    void WriteNcShowImage(QFile& file_, NNcShow::NcShowImage* pShowImage_)
    {
        QString _str = QString::asprintf(
                    "NcShowImage\n");
        QByteArray _nByteArr = _str.toUtf8();
        file_.write(_nByteArr);
        file_.flush();
    }

    void WriteNcShow(QFile& file_, NNcShow::NcShow* pShow_)
    {
        //NNcShow::NCSHOW_TYPE _nType = pShow_->GetType();
        if(pShow_->GetType() == NNcShow::NCSHOW_TYPE::_TIP)
        {
            WriteNcShowTip(file_, (NNcShow::NcShowTip*)pShow_);
        }

        if(pShow_->GetType() == NNcShow::NCSHOW_TYPE::_CONTROL)
        {
            WriteNcShowControl(file_, (NNcShow::NcShowControl*)pShow_);
        }

        if(pShow_->GetType() == NNcShow::NCSHOW_TYPE::_IMAGE)
        {
            WriteNcShowImage(file_, (NNcShow::NcShowImage*)pShow_);
        }
    }

    void ProcessNcStepThread::run()
    {
        m_nState = PRODUCER_RUNNING;

        // For Debug
        QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile(
                    (char*)"4_processncstep_test");
        QFile _file;
        _file.close();
        _file.setFileName(_filepath);
        bool _bRet = _file.open(
                    QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        if(!_bRet)
        {
            assert(false);
        }

        // Just For Debug
        int _nCount = 0;
        while(!m_bStop)
        {
            _nCount++;
            NNcStep::NcStep* _pNcStep = nullptr;
            int _nRet = m_pNcStepBuffer->Pop(_pNcStep);
            // for ncstepbuffer,
            // we are consumer
            // meanning we successly get a ncstep
            if(_nRet == 1)
            {
                // ok
            }
            // meanning the producer of the ncstepbuffer has normally end
            // this is the time we have consumer all ncstep
            // as a producer this is the time we complete the producing
            else if(_nRet == 0)
            {
                m_nState = PRODUCER_NORMAL_END;
                break;
            }
            // meanning the producer of the ncstepbuffer has abnormally end
            // and now we have not any more ncstep to consumer
            // so as a producer of ncshow,we are stopped abnormally
            else
            {
                m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END;
                break;
            }

            if(_pNcStep)
            {

                _pNcStep->GetNcShowPrepare();

                //QWidget* pWidget_,
                //NDataStruct::DynArray<NModel::Part*>& arrParts_,
                //NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>& nNcStepBuffer_
                NNcShow::NcShow* _pShow = _pNcStep->GetNcShow(
                            m_pWidget,
                            m_arrParts,
                            m_nKeyAllocator,
                            m_pNcStepBuffer);
                if(_pShow == nullptr)
                {
                    delete _pShow;
                    m_nState = PRODUCER_ABNORMAL_END_AS_UNEXPECTED;
                    break;
                }

                // Resource Manager
                WriteNcShow(_file, _pShow);
                int _nRetSyn = m_pNcShowBuffer->Push(_pShow);
                if(_nRetSyn == 1)
                {
                    // ok
                }
                // for ncshowbuffer we are producer
                // if return 0,meaning the consumer has normally end
                // this cannot be happend
                else if(_nRetSyn == 0)
                {
                    // this cannot be happend
                    assert(false);
                    m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END;
                    break;
                }
                // for ncshowbuffer we are producer
                // if return -1,meaning the consumer has abnormally end
                // so we need stop producing immediately
                else
                {
                    m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END;
                    break;
                }

                delete _pNcStep;
                _pNcStep = nullptr;
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
            m_pNcShowBuffer->SetProducerState(NSyn::OBJECT_STATE::NORMALLY_END);
        }

        if(m_nState == PRODUCER_ABNORMAL_END_SELF
            || m_nState == PRODUCER_ABNORMAL_END_AS_UNEXPECTED
            || m_nState == PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END
            || m_nState == PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END)
        {
            m_pNcShowBuffer->SetProducerState(NSyn::OBJECT_STATE::ABNORMALLY_END);
        }
    }
}

