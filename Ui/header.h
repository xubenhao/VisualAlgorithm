#ifndef APP_UI_HEADER_H
#define APP_UI_HEADER_H
#include "Global/lib.h"
#include "ModelManager/lib.h"
#include "NcManager/lib.h"
#include "Functions/lib.h"
#include "Parameter/lib.h"
#include "FileGenerate/lib.h"
#include "FileParse/lib.h"
#include "AnimationService/lib.h"

struct ArrayItem
{
    ArrayItem()
    {
        m_nId = -1;
        m_nCapacity = 0;
    }

    int m_nId;
    int m_nCapacity;
};
Q_DECLARE_METATYPE(ArrayItem)
#endif // HEADER_H
