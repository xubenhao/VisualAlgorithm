//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "animationservice.h"

namespace NAnimationService
{
    AnimationService::AnimationService(QObject* parent)
        : QObject(parent)
    {
        m_pParseNcThread = nullptr;
        m_pInterpolateNcCodeThread = nullptr;
        m_pProcessNcStepThread = nullptr;
        m_pTimerRefreshThread = nullptr;
    }

    bool AnimationService::StartArray(
            const QString& strNcFilePath_,
            const NParameter::ArrayNcParameter& arrParam_,
            const NFileParse::ArrayModalData& arrModalData_,
            NDataStruct::DynArray<NModel::Part*>& arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
            QWidget* pWidget_)
    {
        if(GetState() == THREAD_STATE::THREAD_PAUSED
            || GetState() == THREAD_STATE::THREAD_RUNNING)
        {
            return false;
        }

        m_nNcCodeBuffer.Reset();
        m_nNcStepBuffer.Reset();
        m_nNcShowBuffer.Reset();
        if(m_pParseNcThread != nullptr)
        {
            delete m_pParseNcThread;
            m_pParseNcThread = nullptr;
        }

        m_pParseNcThread = new ParseNcThread(
                    strNcFilePath_,
                    arrParam_,
                    arrModalData_,
                    &m_nNcCodeBuffer,
                    this);
        if(m_pInterpolateNcCodeThread != nullptr)
        {
            delete m_pInterpolateNcCodeThread;
            m_pInterpolateNcCodeThread = nullptr;
        }

        m_pInterpolateNcCodeThread = new InterpolateNcCodeThread(
                    arrParam_,
                    arrModalData_,
                    &m_nNcCodeBuffer,
                    &m_nNcStepBuffer,
                    this);

        if(m_pProcessNcStepThread != nullptr)
        {
            delete  m_pProcessNcStepThread;
            m_pProcessNcStepThread = nullptr;
        }

        m_pProcessNcStepThread = new ProcessNcStepThread(
                    pWidget_,
                    arrParts_,
                    nKeyAllocator_,
                    &m_nNcStepBuffer,
                    &m_nNcShowBuffer,
                    this);

        if(m_pTimerRefreshThread != nullptr)
        {
            delete  m_pTimerRefreshThread;
            m_pTimerRefreshThread = nullptr;
        }

        m_pTimerRefreshThread = new TimerRefreshThread(
                    &m_nNcShowBuffer,
                    pWidget_,
                    nullptr);
        m_pParseNcThread->start();
        m_pInterpolateNcCodeThread->start();
        m_pProcessNcStepThread->start();
        //m_pTimerRefreshThread->start();
        return true;
    }


    // Ret:
    // 1 : Success Get
    // 0 : Nothing to Get, Normally End
    // -1: Nothing to Get, AbNormally End
    // 2 : Current Have Not a NcShow To Get. Need Wait
    int AnimationService::TryGetNcShow(NNcShow::NcShow** ppNcShow_)
    {
        NNcShow::NcShow* _pNcShow = nullptr;
        int _nRet = m_nNcShowBuffer.TryPop(_pNcShow);
        // for ncstepbuffer,
        // we are consumer
        // meanning we successly get a ncstep
        if(_nRet == 1)
        {
            // ok
            *ppNcShow_ = _pNcShow;
        }

        return _nRet;
    }

    THREAD_STATE AnimationService::GetState()
    {
        if(m_pParseNcThread)
        {
            return m_pParseNcThread->GetThreadState();
        }
        else
        {
            return THREAD_STATE::THREAD_NOT_START;
        }
        // to do
        //if(m_pTimerRefreshThread)
        //{
        //    m_pTimerRefreshThread->GetThreadState();
        //}
        //else
        //{
        //    return THREAD_NOT_START;
        //}
    }

    void AnimationService::PauseAnimation()
    {
        //m_nTimerRefreshThread.Pause();
    }

    void AnimationService::StopAnimation()
    {
        m_pTimerRefreshThread->Stop();
        m_pProcessNcStepThread->Stop();
        m_pInterpolateNcCodeThread->Stop();
        m_pParseNcThread->Stop();
        delete m_pTimerRefreshThread;
        m_pTimerRefreshThread = nullptr;
        delete m_pProcessNcStepThread;
        m_pProcessNcStepThread = nullptr;
        delete m_pInterpolateNcCodeThread;
        m_pInterpolateNcCodeThread = nullptr;
        delete m_pParseNcThread;
        m_pParseNcThread = nullptr;
    }
}

