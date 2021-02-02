//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "parsencthread.h"

namespace NAnimationService
{
    ParseNcThread::ParseNcThread(
        const QString& strFilePath_,
        const NParameter::ArrayNcParameter& arrParam_,
        const NFileParse::ArrayModalData& arrModalData_,
        NSync::FixBufferFor1P1C<NNcCode::NcCode*, 100>* pNcBuffer_,
        QObject* pParent_)
        : QThread(pParent_), m_strFilePath(strFilePath_), m_pNcCodeBuffer(pNcBuffer_)
    {
        m_bStop = false;
        //m_nParam = arrParam_;
        //m_nModalData = arrModalData_;
        m_pNcCodeBuffer = pNcBuffer_;
        m_pArrayNcFileParse = new NFileParse::ArrayNcFileParse(
                    strFilePath_,
                    arrParam_,
                    arrModalData_,
                    this);
        //m_pArrayNcFileParse->setParent(this);
        m_nState = PRODUCER_NOT_START;
    }

    ParseNcThread::~ParseNcThread()
    {

    }

    void ParseNcThread::Stop()
    {
        m_bStop = true;
    }

    THREAD_STATE ParseNcThread::GetThreadState()
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

    void WriteNcCodeTip(QFile& file_, NNcCode::NcCodeTip* pTip_)
    {
        // Just For Debug WriteNcCode
        QString _str = QString::asprintf(
                    "NcTip:%s\n",
                    pTip_->GetTip());
        QByteArray _nByteArr = _str.toUtf8();
        file_.write(_nByteArr);
        file_.flush();
    }

    void WriteNcCodeControl(QFile& file_, NNcCode::NcCodeControl* pNcCode_)
    {
        // Just For Debug WriteNcCode
        QString _str = QString::asprintf(
                    "NcControl:%d\n",
                    pNcCode_->GetEnableRefresh());
        QByteArray _nByteArr = _str.toUtf8();
        file_.write(_nByteArr);
        file_.flush();
    }

    void WriteNcCodeColor(QFile& file_, NNcCode::NcCodeColor* pNcCode_)
    {
        for(int i = 0; i < pNcCode_->GetColorObjSize(); i++)
        {
            ColorObj _nObj = pNcCode_->GetColorObj(i);
            QString _str = QString::asprintf(
                        "NcColor:Name=%s,Color_R=%d,Color_G=%d,Color_B=%d,Color_A=%d\n",
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

    void WriteNcCodeMove(QFile& file_, NNcCode::NcCodeMove* pNcCode_)
    {
        for(int i = 0; i < pNcCode_->GetMoveObjSize(); i++)
        {
            NNcCode::MoveObj _nObj = pNcCode_->GetMoveObj(i);
            QString _str = QString::asprintf(
                        "NcMove:Name=%s,Type=%d,DeltaLen=%.f\n",
                        _nObj.m_strObjName,
                        pNcCode_->GetMoveType(),
                        _nObj.m_nLengthDelta);
            QByteArray _nByteArr = _str.toUtf8();
            file_.write(_nByteArr);
            file_.flush();
        }
    }

    void WriteNcCode(QFile& file_, NNcCode::NcCode* pNcCode_)
    {
        NNcCode::NCCODE_TYPE _nType = pNcCode_->GetType();
        if(_nType == NNcCode::NCCODE_TYPE::_TIP)
        {
            WriteNcCodeTip(file_, (NNcCode::NcCodeTip*)pNcCode_);
        }

        if(_nType == NNcCode::NCCODE_TYPE::_CONTROL)
        {
            WriteNcCodeControl(file_, (NNcCode::NcCodeControl*)pNcCode_);
        }

        if(_nType == NNcCode::NCCODE_TYPE::_COLOR)
        {
            WriteNcCodeColor(file_, (NNcCode::NcCodeColor*)pNcCode_);
        }

        if(_nType == NNcCode::NCCODE_TYPE::_MOVE)
        {
            WriteNcCodeMove(file_, (NNcCode::NcCodeMove*)pNcCode_);
        }
    }

    // Role:Producer Only
    // Generate NcCode
    void ParseNcThread::run()
    {
        m_nState = PRODUCER_RUNNING;
        // For Debug
        QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"4_test");
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
            NNcCode::NcCode* _pNcCode;
            // Get NcCode According Nc File
            NFileParse::NCFILE_PARSE_RET_CODE _nRet = m_pArrayNcFileParse->GetNcCode(&_pNcCode);
            if(_nRet == NFileParse::NC_FILE_END)
            {
                // Producer End Normally
                m_nState = PRODUCER_NORMAL_END;
                break;
            }
            else if(_nRet == NFileParse::NC_SUCCESS)
            {
                // ok, do nothing
            }
            else
            {
                qDebug("Parse nc error:%d", _nRet);
                m_nState = PRODUCER_ABNORMAL_END_AS_UNEXPECTED;
                break;
            }

            // for debug
            WriteNcCode(_file, _pNcCode);

            int _nRetSyn = m_pNcCodeBuffer->Push(_pNcCode);
            if(_nRetSyn == 1)
            {
                // ok
            }
            else if(_nRetSyn == 0)
            {
                // consumer normally end
                assert(false);
                m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END;
                break;
            }
            else
            {
                m_nState = PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END;
                break;
            }
        }

        // 1.We are producer,Every loop we produce a nc code
        // 2.There is a consumer,continuely consumer the nc codes we produced
        // for the state
        // at beginning
        // we are in idle
        // when start run
        // we are in running
        // when we have produced all the nc codes
        // we are in normal-end[as a producer,we normally end]
        // when we are stopped during running
        // we are in abnormal-end[as a produces,we abnormally end]
        // when we put the nc code into the buffer,
        // and fail because of the consumer has abnormally-end[must be abnormally-end]
        // this time if we continue to put,then the putted nc code we wil not be consumed
        // thus,we should'n put and should stop producing
        // so,we are in abnormal-end[as the consumer has ended,so we have to end too]

        if(m_bStop)
        {
            m_nState = PRODUCER_ABNORMAL_END_SELF;
        }

        // we are role to the NcCodeBuffer are producer
        // so we can only set the producer's state to the NcCodeBuffer
        // we are role to the NcCodeBuffer are producer
        // the consumer's state is a information we can get from the nccodebuffer,
        // influencing our activity.
        if (m_nState == PRODUCER_NORMAL_END)
        {
            m_pNcCodeBuffer->SetProducerState(NSyn::OBJECT_STATE::NORMALLY_END);
        }

        if(m_nState == PRODUCER_ABNORMAL_END_SELF
            || m_nState == PRODUCER_ABNORMAL_END_AS_UNEXPECTED
            || m_nState == PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END
            || m_nState == PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END)
        {
            m_pNcCodeBuffer->SetProducerState(NSyn::OBJECT_STATE::ABNORMALLY_END);
        }

        // when the consumer abnormally end
        // the producer we stop produce
        // the assmeblly is stopped now
        // and must restart if we want to use it again
        // the nc-code in the buffer that can consume, becoming useless, will be destroy later
    }
}

