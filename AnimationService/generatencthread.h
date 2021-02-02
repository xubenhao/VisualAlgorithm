#ifndef ANIMATION_SERVICE_GENERATENCTHREAD_H
#define ANIMATION_SERVICE_GENERATENCTHREAD_H
#include "header.h"

namespace NAnimationService
{
    class GenerateNcThread : public QThread
    {
    public:
        GenerateNcThread();

        void Stop();

    protected:
        void run() override;

    private:
        bool m_bStop;
    };
}


#endif // GENERATENCTHREAD_H
