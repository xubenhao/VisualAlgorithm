#ifndef ANIMATION_SERVICE_INTERPOLATENCCODETHREAD_H
#define ANIMATION_SERVICE_INTERPOLATENCCODETHREAD_H
#include "header.h"

namespace NAnimationService
{
    class InterpolateNcCodeThread : public QThread
    {
    public:
        // Interpolate
        // In:
        // NcCodeBuffer
        // Out:
        // NcStepBuffer
        InterpolateNcCodeThread(
            const NParameter::ArrayNcParameter& arrParam_,
            const NFileParse::ArrayModalData& arrModalData_,
            NSync::FixBufferFor1P1C<NNcCode::NcCode*, 100>* pNcCodeBuffer_,
            NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_,
            QObject* pParent_ = nullptr);
        ~InterpolateNcCodeThread();
        void Stop();
        ASSEMBLYLINEOBJECT_PRODUCER_STATE GetAssemBlyObjectState(){return m_nState;}
        THREAD_STATE GetThreadState();
    protected:
        void run() override;

    private:
        bool m_bStop;

        NParameter::ArrayNcParameter m_nParam;
        NFileParse::ArrayModalData m_nModalData;
        NSync::FixBufferFor1P1C<NNcCode::NcCode*, 100>* m_pNcCodeBuffer;
        NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* m_pNcStepBuffer;
        ASSEMBLYLINEOBJECT_PRODUCER_STATE m_nState;
    };
}



#endif // INTERPOLATENCCODETHREAD_H
