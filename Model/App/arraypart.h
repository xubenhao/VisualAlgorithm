//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef MODEL_ARRAYPART_H
#define MODEL_ARRAYPART_H
#include "Model/header.h"
#include "Model/movablepart.h"

namespace NModel
{
    enum ARRAY_TYPE
    {
        ELEMENT,
        ELEMENT_ADDRESS,
        ELEMENT_INDEX,
        ELEMENT_SCALE,
    };

    class ArrayPart : public MovablePart
    {
    public:
        ArrayPart(ARRAY_TYPE nType_ = ELEMENT, QObject* parent = nullptr);
        ARRAY_TYPE GetArrayType(){return m_nType;}
        void SetArrayType(ARRAY_TYPE nType_){m_nType = nType_;}
        virtual MODEL_TYPE GetType() const{return MODEL_APP_ARRAYPART;}
        virtual void OutputDebugInfo(QFile& hFile_);

    private:
        ARRAY_TYPE m_nType;
    };
}


#endif // ARRAYPART_H
