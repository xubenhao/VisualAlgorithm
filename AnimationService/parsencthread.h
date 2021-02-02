#ifndef ANIMATION_SERVICE_PARSENCTHREAD_H
#define ANIMATION_SERVICE_PARSENCTHREAD_H
#include "header.h"

namespace NAnimationService
{
    class ParseNcThread : public QThread
    {
    public:
        ParseNcThread(
            const QString& strFilePath_,
            const NParameter::ArrayNcParameter& arrParam_,
            const NFileParse::ArrayModalData& arrModalData_,
            NSync::FixBufferFor1P1C<NNcCode::NcCode*, 100>* pNcBuffer_,
            QObject* pParent_ = nullptr);
        ~ParseNcThread();
        void Stop();
        ASSEMBLYLINEOBJECT_PRODUCER_STATE GetAssemBlyObjectState(){return m_nState;}
        THREAD_STATE GetThreadState();
    protected:
        void run() override;

    private:
        bool m_bStop;
        NParameter::ArrayNcParameter m_nParam;
        NFileParse::ArrayModalData m_nModalData;
        QString m_strFilePath;
        NSync::FixBufferFor1P1C<NNcCode::NcCode*, 100>* m_pNcCodeBuffer;
        NFileParse::ArrayNcFileParse* m_pArrayNcFileParse;
        ASSEMBLYLINEOBJECT_PRODUCER_STATE m_nState;
    };
}


#endif // PARSENCTHREAD_H
