//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayintroducedrawingwidget.h"

ArrayIntroduceDrawingWidget::ArrayIntroduceDrawingWidget(
        QWidget *parent) : QWidget(parent)
{
    //setPalette(QPalette(Qt::white));
    //setAutoFillBackground(true);
    Initialize();
}

void ArrayIntroduceDrawingWidget::Initialize()
{
   ResetAllParts();
}

void ArrayIntroduceDrawingWidget::ResetAllParts()
{
    for (int i = 0; i < m_arrParts.GetSize(); i++)
    {
        delete m_arrParts[i];
        m_arrParts[i] = nullptr;
    }

    m_arrParts.DeleteAll();
    m_arrEleParts.DeleteAll();
    m_arrEleBackGroundParts.DeleteAll();
    NDataStruct::DynArray<NModel::Part*> _arrEleAddrParts;
    NDataStruct::DynArray<NModel::Part*> _arrEleIndexParts;
    NModelManager::ModelManager::Instance()->ArrayModelParse(
        NModelManager::ModelManager::GetGeneralArrayModelFilePath(),
        m_arrEleParts,
        m_arrEleBackGroundParts,
        _arrEleAddrParts,
        _arrEleIndexParts);
     int _nSize = m_arrEleBackGroundParts.GetSize();
     for(int i = 0; i < _nSize; i++)
     {
        m_arrParts.Add(m_arrEleBackGroundParts[i]);
     }

     _nSize = m_arrEleParts.GetSize();
     for(int i = 0; i < _nSize; i++)
     {
         m_arrParts.Add(m_arrEleParts[i]);
     }

     _nSize = _arrEleAddrParts.GetSize();
     for(int i = 0; i < _nSize; i++)
     {
         delete _arrEleAddrParts[i];
         _arrEleAddrParts[i] = nullptr;
     }

     _nSize = _arrEleIndexParts.GetSize();
     for(int i = 0; i < _nSize; i++)
     {
         delete _arrEleIndexParts[i];
         _arrEleIndexParts[i] = nullptr;
     }
}

void ArrayIntroduceDrawingWidget::AdjustInitialTransform()
{
    NParameter::ArrayParameter* _pParam 
        = NParameter::ArrayParameter::GetGeneralParameter();
    QRect _rc = this->rect();
    double _nLeftX 
        = (_rc.width() - _pParam->m_nCapacity * _pParam->m_nElementSize.m_nWidth) / 2.0;
    double _nLeftY 
        = (-_rc.height() + _pParam->m_nElementSize.m_nHeight) / 2.0 + 40;
    NTransform::LinearTransform *_pTrans 
        = new NTransform::LinearTransform(_nLeftX, _nLeftY);
    for (int i = 0; i < m_arrParts.GetSize(); i++)
    {
        NTransform::Transform* _pIniTrans = m_arrParts[i]->GetInitialTransform();
        NTransform::TransformGroup* _pGroupTrans = new NTransform::TransformGroup(m_arrParts[i]);
        if(_pIniTrans)
        {
            _pGroupTrans->Add(_pIniTrans);
            _pIniTrans->setParent(_pGroupTrans);
        }

        NTransform::Transform* _pTemp = _pTrans->DeepCopy();
        _pGroupTrans->Add(_pTemp);
        _pTemp->setParent(_pGroupTrans);
        m_arrParts[i]->SetInitialTransform(_pGroupTrans);
    }

    delete  _pTrans;
}

void ArrayIntroduceDrawingWidget::paintEvent(QPaintEvent* event)
{
    // doing a linear transform let parts show in center at first show
    static bool _bFlag = false;
    if(_bFlag == false)
    {
        _bFlag = true;
        AdjustInitialTransform();
    }

    Q_UNUSED(event);
    QImage image = QImage( this ->size(), QImage::Format_RGB32);
    image.fill(Qt::white);
    int _nSize = m_arrParts.GetSize();
    for(int i = 0; i < _nSize; i++)
    {
        m_arrParts[i]->Draw(&image);
    }

    QPainter painter(this);
    painter.drawImage(rect(), image, image.rect());

    // OutPut All Part's Info For Debug
    // For Debug
    QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"intro_show_test");
    QFile _file;
    _file.close();
    _file.setFileName(_filepath);
    bool _bRet = _file.open(
                QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    if(!_bRet)
    {
        assert(false);
    }

    for(int i = 0; i < m_arrParts.GetSize(); i++)
    {
        m_arrParts[i]->OutputDebugInfo(_file);
    }

    _file.close();
}
