//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef SYNC_FIXBUFFERFOR1P1C_H
#define SYNC_FIXBUFFERFOR1P1C_H
#include "header.h"
namespace NSync
{
    #define TRUE 1
    #define END_OF_FILE 0
    #define ERROR -1

    template <typename T, int N>
    class FixBufferFor1P1C
    {
    public:
        FixBufferFor1P1C();
        ~FixBufferFor1P1C();
        int Push(T nEle_);

        int TryPop(T &nEle_);
        int Pop(T &nEle_);
        int Peek(T &nEle_);
        void SetProducerState(NSyn::OBJECT_STATE nState_);
        NSyn::OBJECT_STATE GetProducerState();
        void SetConsumerState(NSyn::OBJECT_STATE nState_);
        NSyn::OBJECT_STATE GetConsumerState();
        void Reset();
    private:
        QSemaphore m_nSemEmptySlots;
        QSemaphore m_nSemFullSlots;
        NDataStruct::FixQueue<T, N> m_nQueue;
        QMutex m_nMutexState;
        NSyn::OBJECT_STATE m_nProducerState;
        NSyn::OBJECT_STATE m_nConsumerState;
    };

    template <typename T, int N>
    FixBufferFor1P1C<T,N>::FixBufferFor1P1C()
        : m_nSemEmptySlots(N),m_nSemFullSlots(0)
    {
        m_nProducerState = NSyn::OBJECT_STATE::NOT_START;
        m_nConsumerState = NSyn::OBJECT_STATE::NOT_START;
    }

    template <typename T, int N>
    FixBufferFor1P1C<T,N>::~FixBufferFor1P1C()
    {

    }

    // this model like half-duplex reliable packet service
    // write
    // 1.if peer is running or not start, write if can or wait a idel slot,write return 1
    // 2.receive peer's fin[meaning that the peer has normally ended],write return 0
    // 2.receive peer's rst[meaning that the peer has abnormally ended],write return -1
    template <typename T, int N>
    int FixBufferFor1P1C<T,N>::Push(T pCode_)
    {
        int _nRet = 1;
        QMutexLocker _nLocker(&m_nMutexState);
        if(m_nProducerState == NSyn::OBJECT_STATE::NOT_START)
        {
            m_nProducerState = NSyn::OBJECT_STATE::RUNNING;
        }

        if(m_nConsumerState == NSyn::OBJECT_STATE::NOT_START
            || m_nConsumerState == NSyn::OBJECT_STATE::RUNNING)
        {
            _nRet = 1;
        }
        else if(m_nConsumerState == NSyn::OBJECT_STATE::NORMALLY_END)
        {
            // when the producer is running,
            // the consumer cannot stop normally.
            assert(false);
            _nRet = 0;
        }
        else
        {
            _nRet = -1;
        }


        if(_nRet != 1)
        {
            return _nRet;
        }

        _nLocker.unlock();
        // 1.not lock resource
        // here is a question
        // first,at the time arriving here,the consumer's state must be not-start/running
        // if there is no empty slot,and the only producer is waitting
        // but if during the waitting,the consumer's state change to fin/rst.
        // if we keep waittng,because no consumer,we won't wait a empty slot forever
        // dead lock

        // ---resolve way
        // if the consumer changes its state to fin/rst
        // it needs release a empty slot to prevent the producer continuely blocked in waitting for a empty slot

        // 2.lock resource
        // first,at the time arriving here,the consumer's state must be not-start/running
        // if there is no empty slot,and the only producer is waitting
        // but if during the waitting,the consumer try to change its state to fin/rst.
        // because we lock the resource,
        // the consumer will wait until we release the source
        // because we wait the consumer to release a empty slot
        // we will wait until the consumer release a empty slot
        // dead lock
        // --cannot resolve
        m_nSemEmptySlots.acquire();
        if(m_nQueue.Size() >= N)
        {
            // because we have synchronization between producing and consuming
            // so this won't happen.
            assert(false);
            m_nSemEmptySlots.release();
            return 0;
        }

        QMutexLocker _nLocker2(&m_nMutexState);
        if(m_nConsumerState == NSyn::OBJECT_STATE::NORMALLY_END)
        {
            m_nSemEmptySlots.release();
            assert(false);
            return 0;
        }
        else if(m_nConsumerState == NSyn::OBJECT_STATE::ABNORMALLY_END)
        {
            m_nSemEmptySlots.release();
            return -1;
        }

        m_nQueue.In(pCode_);
        m_nSemFullSlots.release();
        return _nRet;
    }

    template <typename T, int N>
    int FixBufferFor1P1C<T,N>::TryPop(T &nEle_)
    {
        // 1.not lock resource
        // here is a question
        // if there is no full slot,and the only consumer is waitting
        // but if during the waitting,the producer's state change to fin/rst.
        // if we keep waittng,because no producer,we won't wait a full slot forever
        // dead lock
        // ---resolve way
        // if the producer changes its state to fin/rst
        // it needs release a full slot to prevent the consumer continuely blocked in waitting for a full slot
        bool _bFlag = m_nSemFullSlots.tryAcquire();
        if(!_bFlag)
        {
            return 2;
        }

        if(m_nConsumerState == NSyn::OBJECT_STATE::NOT_START)
        {
            m_nConsumerState == NSyn::OBJECT_STATE::RUNNING;
        }

        QMutexLocker _nLocker(&m_nMutexState);
        if(m_nProducerState == NSyn::OBJECT_STATE::RUNNING)
        {
            // ok
            nEle_ = m_nQueue.Out();
            m_nSemEmptySlots.release();
            return 1;
        }
        else if(m_nProducerState == NSyn::OBJECT_STATE::NORMALLY_END)
        {
            int _nNum = m_nSemFullSlots.available();
            if(_nNum == 0)
            {
                m_nSemFullSlots.release();
                return 0;
            }
            else
            {
                nEle_ = m_nQueue.Out();
                m_nSemEmptySlots.release();
                return 1;
            }
        }
        else if(m_nProducerState == NSyn::OBJECT_STATE::ABNORMALLY_END)
        {
            int _nNum = m_nSemFullSlots.available();
            if(_nNum == 0)
            {
                m_nSemFullSlots.release();
                return -1;
            }
            else
            {
                nEle_ = m_nQueue.Out();
                m_nSemEmptySlots.release();
                return 1;
            }
        }
        else
        {
           assert(false);
           m_nSemFullSlots.release();
           return -1;
        }
    }

    // read
    // 1.if peer is running or not start,,read if can or wait a full slot,read return 1
    // 2.receive peer's fin[...],read if can and return 1,if not have a full slot to read at the time,read return 0
    // 3.receive peer's rst[...],read if can and return 1,if not have a full slot to read at the time,read return -1
    template <typename T, int N>
    int FixBufferFor1P1C<T,N>::Pop(T& nEle_)
    {
        // 1.not lock resource
        // here is a question
        // if there is no full slot,and the only consumer is waitting
        // but if during the waitting,the producer's state change to fin/rst.
        // if we keep waittng,because no producer,we won't wait a full slot forever
        // dead lock
        // ---resolve way
        // if the producer changes its state to fin/rst
        // it needs release a full slot to prevent the consumer continuely blocked in waitting for a full slot
        m_nSemFullSlots.acquire();
        if(m_nConsumerState == NSyn::OBJECT_STATE::NOT_START)
        {
            m_nConsumerState == NSyn::OBJECT_STATE::RUNNING;
        }

        QMutexLocker _nLocker(&m_nMutexState);
        if(m_nProducerState == NSyn::OBJECT_STATE::RUNNING)
        {
            // ok
            nEle_ = m_nQueue.Out();
            m_nSemEmptySlots.release();
            return 1;
        }
        else if(m_nProducerState == NSyn::OBJECT_STATE::NORMALLY_END)
        {
            int _nNum = m_nSemFullSlots.available();
            if(_nNum == 0)
            {
                m_nSemFullSlots.release();
                return 0;
            }
            else
            {
                nEle_ = m_nQueue.Out();
                m_nSemEmptySlots.release();
                return 1;
            }
        }
        else if(m_nProducerState == NSyn::OBJECT_STATE::ABNORMALLY_END)
        {
            int _nNum = m_nSemFullSlots.available();
            if(_nNum == 0)
            {
                m_nSemFullSlots.release();
                return -1;
            }
            else
            {
                nEle_ = m_nQueue.Out();
                m_nSemEmptySlots.release();
                return 1;
            }
        }
        else
        {
           assert(false);
           m_nSemFullSlots.release();
           return -1;
        }
    }

    template <typename T, int N>
    int FixBufferFor1P1C<T,N>::Peek(T &nEle_)
    {
        // 1.not lock resource
        // here is a question
        // if there is no full slot,and the only consumer is waitting
        // but if during the waitting,the producer's state change to fin/rst.
        // if we keep waittng,because no producer,we won't wait a full slot forever
        // dead lock
        // ---resolve way
        // if the producer changes its state to fin/rst
        // it needs release a full slot to prevent the consumer continuely blocked in waitting for a full slot
        m_nSemFullSlots.acquire();
        QMutexLocker _nLocker(&m_nMutexState);
        if(m_nProducerState == NSyn::OBJECT_STATE::RUNNING)
        {
            // ok
            nEle_ = m_nQueue.Peek();
            m_nSemFullSlots.release();
            //m_nSemEmptySlots.release();
            return 1;
        }
        else if(m_nProducerState == NSyn::OBJECT_STATE::NORMALLY_END)
        {
            int _nNum = m_nSemFullSlots.available();
            if(_nNum == 0)
            {
                m_nSemFullSlots.release();
                return 0;
            }
            else
            {
                nEle_ = m_nQueue.Peek();
                m_nSemFullSlots.release();
                //m_nSemEmptySlots.release();
                return 1;
            }
        }
        else if(m_nProducerState == NSyn::OBJECT_STATE::ABNORMALLY_END)
        {
            int _nNum = m_nSemFullSlots.available();
            if(_nNum == 0)
            {
                m_nSemFullSlots.release();
                return -1;
            }
            else
            {
                nEle_ = m_nQueue.Peek();
                m_nSemFullSlots.release();
                //m_nSemEmptySlots.release();
                return 1;
            }
        }
        else
        {
           assert(false);
           m_nSemFullSlots.release();
           return -1;
        }
    }

    // the state's change is not-revertable
    // it must according to the order:not-start->running->fin/rst
    template <typename T, int N>
    void FixBufferFor1P1C<T,N>::SetProducerState(NSyn::OBJECT_STATE nState_)
    {
        QMutexLocker _nLocker(&m_nMutexState);
        if(nState_ < m_nProducerState)
        {
            return;
        }

        // ---resolve way
        // if the producer changes its state to fin/rst
        // it needs release a full slot to prevent the consumer continuely blocked in waitting for a full slot
        if((m_nProducerState == NSyn::OBJECT_STATE::NOT_START || m_nProducerState == NSyn::OBJECT_STATE::RUNNING)
            && (nState_ == NSyn::OBJECT_STATE::NORMALLY_END || nState_ == NSyn::OBJECT_STATE::ABNORMALLY_END))
        {
            m_nSemFullSlots.release();
        }

        m_nProducerState = nState_;
    }

    template <typename T, int N>
    NSyn::OBJECT_STATE FixBufferFor1P1C<T,N>::GetProducerState()
    {
        QMutexLocker _nLocker(&m_nMutexState);
        return m_nProducerState;
    }

    template <typename T, int N>
    void FixBufferFor1P1C<T,N>::SetConsumerState(NSyn::OBJECT_STATE nState_)
    {
        QMutexLocker _nLocker(&m_nMutexState);
        if(nState_ < m_nConsumerState)
        {
            assert(false);
            return;
        }

        if(m_nProducerState != NSyn::OBJECT_STATE::NORMALLY_END
            && nState_ == NSyn::OBJECT_STATE::NORMALLY_END)
        {
            assert(false);
            return;
        }

        // ---resolve way
        // if the consumer changes its state to fin/rst
        // it needs release a empty slot to prevent the producer continuely blocked in waitting for a empty slot
        if((m_nConsumerState == NSyn::OBJECT_STATE::NOT_START || m_nConsumerState == NSyn::OBJECT_STATE::RUNNING)
            && (nState_ == NSyn::OBJECT_STATE::NORMALLY_END || nState_ == NSyn::OBJECT_STATE::ABNORMALLY_END))
        {
            m_nSemEmptySlots.release();
        }

        m_nConsumerState = nState_;
    }

    template <typename T, int N>
    NSyn::OBJECT_STATE FixBufferFor1P1C<T,N>::GetConsumerState()
    {
        QMutexLocker _nLocker(&m_nMutexState);
        return m_nConsumerState;
    }

    template <typename T, int N>
    void FixBufferFor1P1C<T,N>::Reset()
    {
        // When do this
        // the consumer and the producer all should in stop state
        QMutexLocker _nLocker(&m_nMutexState);
        if(m_nConsumerState == NSyn::OBJECT_STATE::RUNNING
            || m_nProducerState == NSyn::OBJECT_STATE::RUNNING)
        {
            assert(false);
            return;
        }

        m_nConsumerState = NSyn::OBJECT_STATE::NOT_START;
        m_nProducerState = NSyn::OBJECT_STATE::NOT_START;
        int _nNum = m_nSemEmptySlots.available();
        m_nSemFullSlots.release(N - _nNum);
        _nNum = m_nSemFullSlots.available();
        m_nSemFullSlots.acquire(_nNum);
        assert(m_nSemFullSlots.available() == 0);
        assert(m_nSemEmptySlots.available() == N);
    }
}


#endif // FIXBUFFERFOR1P1C_H
