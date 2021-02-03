//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCCODE_COLOR_H
#define NCCODE_COLOR_H
#include "nccode.h"

namespace NNcCode
{
    class NcCodeColor : public NcCode
    {
    public:
        NcCodeColor(QObject *parent = nullptr);
        int GetColorObjSize(){return m_arrColorObjs.GetSize();}
        void AddColorObj(const ColorObj& nObj_){m_arrColorObjs.Add(nObj_);}
        void DeleteColorObj(const ColorObj& nObj_){m_arrColorObjs.DeleteByValue(nObj_);}
        ColorObj GetColorObj(int nIndex_)
        {
            if(nIndex_ >= 0 && nIndex_ < m_arrColorObjs.GetSize())
            {
                return m_arrColorObjs[nIndex_];
            }

            assert(false);
            return ColorObj();
        }
        virtual NCCODE_TYPE GetType(){return NCCODE_TYPE::_COLOR;}
        NcCode* DeepCopy();
        virtual void GetNcStepPrepare();
        virtual NNcStep::NcStep* GetNcStep();

    private:
        NDataStruct::DynArray<ColorObj> m_arrColorObjs;

        int m_nCurTimes;
    };
}


#endif // COLOR_H
