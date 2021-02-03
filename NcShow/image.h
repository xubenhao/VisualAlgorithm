//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef NC_SHOW_IMAGE_H
#define NC_SHOW_NCSHOWIMAGE_H
#include "ncshow.h"

namespace NNcShow
{
    class NcShowImage : public NcShow
    {
    public:
        NcShowImage(QObject *parent = nullptr);
        virtual NCSHOW_TYPE GetType(){return NCSHOW_TYPE::_IMAGE;}
        virtual NcShow* DeepCopy();
        QImage GetImage(){return m_nImage;}
        void SetImage(const QImage& nImage_){m_nImage = nImage_;}
    private:
        QImage m_nImage;
    };
}


#endif // NCSHOWIMAGE_H
