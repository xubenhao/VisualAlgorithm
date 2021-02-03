//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NCSTEP_COLOR_H
#define NCSTEP_COLOR_H

#include "ncstep.h"
namespace NNcStep
{
    class NcStepColor : public NcStep
    {
    public:
        NcStepColor(QObject *parent = nullptr);
        ColorObj GetColorObj(int nIndex_)
        {
            if(nIndex_ >= 0 && nIndex_ < m_arrColorObjs.GetSize())
            {
                return m_arrColorObjs[nIndex_];
            }

            assert(false);
            return ColorObj();
        }
        int GetColorObjSize(){return m_arrColorObjs.GetSize();}
        void AddColorObj(const ColorObj& nObj_){m_arrColorObjs.Add(nObj_);}
        void DeleteColorObj(const ColorObj& nObj_){m_arrColorObjs.DeleteByValue(nObj_);}
        virtual NCSTEP_TYPE GetType(){return NCSTEP_TYPE::_COLOR;}
        virtual NcStep* DeepCopy();
        virtual void GetNcShowPrepare();
        virtual NNcShow::NcShow* GetNcShow(
                QWidget* pWidget_,
                NDataStruct::DynArray<NModel::Part*>& arrParts_,
                NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
                NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_);

    private:
        NDataStruct::DynArray<ColorObj> m_arrColorObjs;
        int m_nCurTimes;
    };

}

#endif // COLOR_H
