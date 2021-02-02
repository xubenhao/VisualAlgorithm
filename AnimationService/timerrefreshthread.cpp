#include "timerrefreshthread.h"
#include "Ui/Drawing/arrayvaluevisitdrawingwidget.h"
#include <QTimer>
namespace NAnimationService
{
    void TimerRefreshThread::Pause()
    {

    }

    TimerRefreshThread::TimerRefreshThread(
        //const NParameter::ArrayNcParameter& arrParam_,
        //const NFileParse::ArrayModalData& arrModalData_,
        NSync::FixBufferFor1P1C<NNcShow::NcShow*, 20>* pNcShowBuffer_,
        QWidget* pWidget_,
        QObject* pParent_)
        : QThread(pParent_)
    {
        //m_nParam = arrParam_;
        //m_nModalData = arrModalData_;
        //m_pNcCodeBuffer = pNcCodeBuffer_;
        //m_pNcStepBuffer = pNcStepBuffer_;
        m_pNcShowBuffer = pNcShowBuffer_;
        m_pWidget = pWidget_;
        m_bStop = false;
        m_nState = PRODUCER_NOT_START;
        m_pTimer = nullptr;
    }

    TimerRefreshThread::~TimerRefreshThread()
    {

    }

    void TimerRefreshThread::Stop()
    {
        m_bStop = true;
    }

    THREAD_STATE TimerRefreshThread::GetThreadState()
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

    void TimerRefreshThread::Update()
    {
        // for every object in the assembly line
        // it actor as a producer and a consumer
        // we need to process the state of the object
        if(!m_bStop)
        {
            NNcShow::NcShow* _pNcShow = nullptr;
            int _nRet = m_pNcShowBuffer->Pop(_pNcShow);
            if(_nRet == 1)
            {
                // ok
            }
            else if(_nRet == 0)
            {
                // producer normally end
                assert(false);
                m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END;
            }
            else
            {
                m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END;
            }

            if(_nRet == 1 && _pNcShow)
            {
                // Consumer a NcShow
                ArrayValueVisitDrawingWidget* _pW = (ArrayValueVisitDrawingWidget*)m_pWidget;
                _pW->ProcessNcShow(_pNcShow);
                delete _pNcShow;
            }
        }

        if(m_bStop || m_nState != PRODUCER_RUNNING)
        {
            pthread_exit(nullptr);
        }
    }

    void TimerRefreshThread::timerEvent(QTimerEvent *event)
    {
        if(event->timerId() == m_nTimerId)
        {
            Update();
        }
    }

    void TimerRefreshThread::run()
    {
        m_nState = PRODUCER_RUNNING;
        //m_nTimerId = startTimer(20);
        m_pTimer = new QTimer(this);
        connect(m_pTimer, SIGNAL(timeout()), this, SLOT(Update()), Qt::DirectConnection);
        //m_pTimer->start(20);
        exec();
    }
}

