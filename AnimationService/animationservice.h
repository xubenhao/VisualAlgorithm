//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef ANIMATION_SERVICE_ANIMATIONSERVICE_H
#define ANIMATION_SERVICE_ANIMATIONSERVICE_H
#include "header.h"
#include "generatencthread.h"
#include "parsencthread.h"
#include "interpolatenccodethread.h"
#include "processncstepthread.h"
#include "timerrefreshthread.h"

namespace NAnimationService
{
    enum SERIVICE_STATE
    {
        SERVICE_IDLE,
        SERVICE_RUNNING,
        SERVICE_PAUSE,
    };

    class AnimationService : public QObject
    {
        Q_OBJECT
    public:
        explicit AnimationService(QObject* parent = nullptr);
        explicit AnimationService(
            const QString& strFilePath_,
            const NParameter::ArrayNcParameter& arrParam_,
            const NFileParse::ArrayModalData& arrModalData_,
            QObject *parent = nullptr);

    public:

        THREAD_STATE GetState();
        int TryGetNcShow(NNcShow::NcShow** ppNcShow_);
        bool StartArray(
            const QString& strNcFilePath_,
            const NParameter::ArrayNcParameter& arrParam_,
            const NFileParse::ArrayModalData& arrModalData_,
            NDataStruct::DynArray<NModel::Part*>& arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator,
            QWidget* pWidget_);


        NNcShow::NcShow* GetNcShow();
        // to do
        // support multi-start
        void StartAnimation();
        void PauseAnimation();
        void StopAnimation();
        //void ResumeAnimation();

        //void StepStartAnimation();
        //void StepContinue();
        //void StepStop();
    signals:

    private:
        ParseNcThread* m_pParseNcThread;
        InterpolateNcCodeThread* m_pInterpolateNcCodeThread;
        ProcessNcStepThread* m_pProcessNcStepThread;
        TimerRefreshThread* m_pTimerRefreshThread;

        NSync::FixBufferFor1P1C<NNcCode::NcCode*, 100> m_nNcCodeBuffer;
        NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100> m_nNcStepBuffer;
        NSync::FixBufferFor1P1C<NNcShow::NcShow*, 20> m_nNcShowBuffer;

        SERIVICE_STATE m_nState;

    };
}

#endif // ANIMATIONSERVICE_H
