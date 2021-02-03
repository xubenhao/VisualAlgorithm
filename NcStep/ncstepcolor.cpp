//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "ncstepcolor.h"

namespace NNcStep
{
    NcStepColor::NcStepColor(QObject *parent)
        : NcStep(parent)
    {
        m_nCurTimes = 0;
    }

    NcStep* NcStepColor::DeepCopy()
    {
        NcStepColor* _pCode = new NcStepColor();
        _pCode->m_arrColorObjs = m_arrColorObjs;
        _pCode->m_nCurTimes = m_nCurTimes;
        return _pCode;
    }

    void NcStepColor::GetNcShowPrepare()
    {
        m_nCurTimes = 0;
    }

    NNcShow::NcShow* NcStepColor::GetNcShow(
            QWidget* pWidget_,
            NDataStruct::DynArray<NModel::Part*>& arrParts_,
            NDataStruct::KeyAllocator<NModel::Part*>& nKeyAllocator_,
            NSync::FixBufferFor1P1C<NNcStep::NcStep*, 100>* pNcStepBuffer_)
    {
        int _nCurTimes = m_nCurTimes++;
        if(_nCurTimes == 0)
        {
            // we use to generate a image use this ncstep
            // when generate a image
            // 1.we need the target widget
            // 2.we need all the showing parts
            // 3.we need for every showing part
            // we need know its curposion and its curcolor
            // because every part's has its curposition and its curcolor info
            // so we just get all showing parts and draw it
            // then we get a image
            // before doing this,
            // we need set the target parts brush-color according the color step
            for(int i = 0; i < m_arrColorObjs.GetSize(); i++)
            {
                ColorObj _nObj = m_arrColorObjs[i];
                // From ObjectId Find Part*
                // This can use KeyAllocator
                NModel::Part* _pPart = nullptr;
                bool _bFlag = nKeyAllocator_.Find(_nObj.m_nObjectId, _pPart);
                assert(_bFlag);
                if(_pPart)
                {
                    NDrawing::Drawing* _pDrawing = _pPart->GetDrawing();
                    QBrush _nBrush;
                    QColor _nColor = QColor(
                                _nObj.m_nColor.m_nR,
                                _nObj.m_nColor.m_nG,
                                _nObj.m_nColor.m_nB,
                                _nObj.m_nColor.m_nA);
                    _nBrush.setColor(_nColor);
                    _nBrush.setStyle(Qt::BrushStyle::SolidPattern);
                    _pDrawing->SetBrush(_nBrush);
                }

                /*for(int j = 0; arrParts_.GetSize(); j++)
                {
                    //if(strcmp(arrParts_[j]->GetName(), _nObj.m_strObjName) == 0)
                    if(arrParts_[j]->GetObjectId() == _nObj.m_nObjectId)
                    {
                        NDrawing::Drawing* _pDrawing = arrParts_[j]->GetDrawing();
                        QBrush _nBrush;
                        QColor _nColor = QColor(
                                    _nObj.m_nColor.m_nR,
                                    _nObj.m_nColor.m_nG,
                                    _nObj.m_nColor.m_nB,
                                    _nObj.m_nColor.m_nA);
                        _nBrush.setColor(_nColor);
                        _nBrush.setStyle(Qt::BrushStyle::SolidPattern);
                        _pDrawing->SetBrush(_nBrush);
                        break;
                    }
                }*/
            }

            QImage image = QImage(pWidget_->size(), QImage::Format_RGB32);
            image.fill(Qt::white);

            int _nSize = arrParts_.GetSize();
            for(int i = 0; i < _nSize; i++)
            {
                arrParts_[i]->Draw(&image);
            }

            NNcShow::NcShowImage* _pImage = new NNcShow::NcShowImage();
            _pImage->SetImage(image);
            return _pImage;
        }
        else if(_nCurTimes == 1)
        {
            return nullptr;
        }
        else
        {
            assert(false);
            return nullptr;
        }
    }
}
