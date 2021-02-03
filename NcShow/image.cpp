//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "image.h"


namespace NNcShow
{
    NcShowImage::NcShowImage(QObject* object)
        : NcShow(object)
    {

    }

    NcShow* NcShowImage::DeepCopy()
    {
        NNcShow::NcShowImage* _pShow = new NNcShow::NcShowImage();
        _pShow->m_nImage = m_nImage;
        return _pShow;
    }
}
