#ifndef ANIMATION_SERVICE_HEADER_H
#define ANIMATION_SERVICE_HEADER_H
#include "Global/lib.h"
#include "DataStruct/lib.h"
#include "NcCode/lib.h"
#include "NcStep/lib.h"
#include "NcShow/lib.h"
#include "FileParse/lib.h"
#include "Sync/lib.h"

// for debug
#include "NcManager/lib.h"

namespace NAnimationService
{
    enum ASSEMBLYLINEOBJECT_PRODUCER_STATE
    {
        PRODUCER_NOT_START,
        PRODUCER_RUNNING,
        PRODUCER_PAUSED,
        PRODUCER_NORMAL_END,
        PRODUCER_ABNORMAL_END_SELF,
        PRODUCER_ABNORMAL_END_AS_CONSUMER_NORMAL_END,
        PRODUCER_ABNORMAL_END_AS_CONSUMER_ABNORAML_END,
        PRODUCER_ABNORMAL_END_AS_UNEXPECTED,
    };

    enum THREAD_STATE
    {
        THREAD_NOT_START,
        THREAD_RUNNING,
        THREAD_PAUSED,
        THREAD_ABNORMALLY_END,
        THREAD_NORMALLY_END,
    };

}
#endif // HEADER_H
