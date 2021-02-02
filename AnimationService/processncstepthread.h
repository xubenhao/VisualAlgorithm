#ifndef ANIMATION_SERVICE_PROCESSNCSTEPTHREAD_H
#define ANIMATION_SERVICE_PROCESSNCSTEPTHREAD_H
#include "header.h"

namespace NAnimationService
{
   class ProcessNcStepThread : public QThread
    {
    public:
        // Interpolate
        // In:
        // NcStepBuffer
        // Out:
        // NcShowBuffer
        ProcessNcStepThread(
            //const NParameter::ArrayNcParameter& arrParam_,
            QWidget* pWidget_,
            NDataStruct::DynArray<NModel::Part*> arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*> nKeyAllocator_,
            NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_,
            NSync::FixBufferFor1P1C<NNcShow::NcShow*, 20>* pNcShowBuffer_,
            QObject* pParent_ = nullptr);
        ~ProcessNcStepThread();
        void Stop();
        ASSEMBLYLINEOBJECT_PRODUCER_STATE GetAssemBlyObjectState(){return m_nState;}
        THREAD_STATE GetThreadState();
    protected:
        void run() override;

    private:
        bool m_bStop;

        //NParameter::ArrayNcParameter m_nParam;
        //NFileParse::ArrayModalData m_nModalData;
        QWidget* m_pWidget;
        NDataStruct::DynArray<NModel::Part*> m_arrParts;
        NDataStruct::KeyAllocator<NModel::Part*> m_nKeyAllocator;
        NSync::FixBufferFor1P1C<NNcShow::NcShow*, 20>* m_pNcShowBuffer;
        NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* m_pNcStepBuffer;
        ASSEMBLYLINEOBJECT_PRODUCER_STATE m_nState;
    };
}


#endif // PROCESSNCSTEPTHREAD_H
