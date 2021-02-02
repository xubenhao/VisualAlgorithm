//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef ANIMATION_SERVICE_TIMERREFRESHTHREAD_H
#define ANIMATION_SERVICE_TIMERREFRESHTHREAD_H
#include "header.h"

namespace NAnimationService
{
    class TimerRefreshThread : public QThread
    {
    public:
        // TimerRefresh
        // In:
        // NcShowBuffer
        // Out:
        // Get nc show and trigger related widget updating
        TimerRefreshThread(
            //const NParameter::ArrayNcParameter& arrParam_,
            //const NFileParse::ArrayModalData& arrModalData_,
            NSync::FixBufferFor1P1C<NNcShow::NcShow*, 20>* pNcShowBuffer_,
            QWidget* pWidget_,
            QObject* pParent_ = nullptr);
        ~TimerRefreshThread();
        void Stop();
        void Pause();
        virtual void timerEvent(QTimerEvent *event);
        ASSEMBLYLINEOBJECT_PRODUCER_STATE GetAssemBlyObjectState(){return m_nState;}
        THREAD_STATE GetThreadState();
    protected:
        void run() override;

    public slots:
        void Update();

    private:
        bool m_bStop;
        QTimer* m_pTimer;


        NSync::FixBufferFor1P1C<NNcShow::NcShow*, 20>* m_pNcShowBuffer;
        QWidget* m_pWidget;
        ASSEMBLYLINEOBJECT_PRODUCER_STATE m_nState;
        int m_nTimerId;
        //std::function<void(*)()>
      };
}

#endif // TIMERREFRESHTHREAD_H
