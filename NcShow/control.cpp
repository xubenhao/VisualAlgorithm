//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "control.h"
namespace NNcShow
{
    NcShowControl::NcShowControl(QObject* object)
        : NcShow(object)
    {
        m_nRefreshEnable = true;
    }

    NcShow* NcShowControl::DeepCopy()
    {
        NcShowControl* _pShowControl = new NcShowControl();
        _pShowControl->m_nRefreshEnable = m_nRefreshEnable;
        return _pShowControl;
    }
}
