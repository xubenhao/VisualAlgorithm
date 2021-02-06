//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayvaluedeletedrawingwidget.h"

ArrayValueDeleteDrawingWidget::ArrayValueDeleteDrawingWidget(QWidget *parent) : QWidget(parent)
{
    Initialize();
    m_nState = -1;
}

void ArrayValueDeleteDrawingWidget::Initialize()
{
    ResetAllParts();
    m_pService = new NAnimationService::AnimationService(this);
    m_nRefreshTimerId = startTimer(20);
}

void ArrayValueDeleteDrawingWidget::timerEvent(QTimerEvent *event)
{
   if(event->timerId() == m_nRefreshTimerId)
   {
        if(m_pService)
        {
            NNcShow::NcShow* _pNcShow = nullptr;
            int _nRet = m_pService->TryGetNcShow(&_pNcShow);
            if(_nRet == 1)
            {
                ProcessNcShow(_pNcShow);
                delete _pNcShow;
                _pNcShow = nullptr;
            }

            // Nothing to Get
            m_nState = _nRet;
        }
   }
}

void ArrayValueDeleteDrawingWidget::AdjustInitialTransform()
{
    // Adjust Part's Initial Transform when first show in client of window
    // to let them more preporty in place
    NParameter::ArrayParameter* _pParam = NParameter::ArrayParameter::GetGeneralParameter();
    QRect _rc = this->rect();
    double _nLeftX = (_rc.width() - _pParam->m_nCapacity * _pParam->m_nElementSize.m_nWidth) / 2.0;
    double _nLeftY = (-_rc.height() + _pParam->m_nElementSize.m_nHeight) / 2.0 + 40;
    NTransform::LinearTransform *_pTrans = new NTransform::LinearTransform(_nLeftX, _nLeftY);
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

void ArrayValueDeleteDrawingWidget::ProcessNcShow(NNcShow::NcShow* pShow_)
{
    switch (pShow_->GetType())
    {
    case NNcShow::NCSHOW_TYPE::_IMAGE:
    {
        NNcShow::NcShowImage* _pImage = (NNcShow::NcShowImage*)pShow_;
        QPainter painter(this);
        m_nImage = _pImage->GetImage();
        //painter.drawImage(rect(), image, image.rect());
        update();
    }
        break;
    case NNcShow::NCSHOW_TYPE::_CONTROL:
    {

    }
        break;
    case NNcShow::NCSHOW_TYPE::_TIP:
    {
        NNcShow::NcShowTip* _pTip = (NNcShow::NcShowTip*)pShow_;
        emit ProcessTip(_pTip);
    }
        break;
    default:
    {
        assert(false);
    }
        break;
    }
}

QImage ArrayValueDeleteDrawingWidget::GetImage()
{
    if(m_nState == 1)
    {
        return m_nImage;
    }
    else
    {
        QImage image = QImage(this ->size(), QImage::Format_RGB32);
        image.fill(Qt::white);
        for (int i = 0; i < m_arrParts.GetSize(); i++)
        {
            m_arrParts[i]->Draw(&image);
        }

        return image;
    }
}

void ArrayValueDeleteDrawingWidget::paintEvent(QPaintEvent* event)
{
    // doing a linear transform let parts show in center at first show
    static bool _bFlag = false;
    if(_bFlag == false)
    {
        _bFlag = true;
        AdjustInitialTransform();
    }

    Q_UNUSED(event);
    QPainter painter(this);
    QImage image = GetImage();
    painter.drawImage(rect(), image, image.rect());
}

void ArrayValueDeleteDrawingWidget::GetArrayParameter(NParameter::ArrayNcParameter& nArrNcParam_)
{
    NParameter::ArrayParameter* _pParam = NParameter::ArrayParameter::GetGeneralParameter();
    //NParameter::ArrayNcParameter _nArrNcParam;
    nArrNcParam_.m_nSize = _pParam->m_nSize;
    nArrNcParam_.m_nCapacity = _pParam->m_nCapacity;
    for (int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        NParameter::ArrayNcElement _nEle;
        _nEle.m_nSize = _pParam->m_nElementSize;
        _nEle.m_nDefault = _pParam->m_arrElements[i].m_nBrush.m_nColor;
        _nEle.m_nMatch = COLOR_11;
        _nEle.m_nNotMatch = COLOR_10;
        strncpy(
            _nEle.m_strContent,
            _pParam->m_arrElements[i].m_nContent,
            sizeof(_nEle.m_strContent));
        strncpy(
            _nEle.m_strName,
            _pParam->m_arrElements[i].m_strName,
            sizeof(_nEle.m_strName));
        _nEle.m_nObjectId = m_arrEleParts[i]->GetObjectId();
        nArrNcParam_.m_arrElements.Add(_nEle);
    }

    nArrNcParam_.m_nDefToFirstLen = 100.0;
    nArrNcParam_.m_nDefToFirstAngle = 90.0;
}

void ArrayValueDeleteDrawingWidget::GetModalParameter(NFileParse::ArrayModalData& nModalData_)
{
    for (int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        NFileParse::MoveObj _nObj;
        strncpy(_nObj.m_strObjName, m_arrEleParts[i]->GetName(), sizeof(_nObj.m_strObjName));
        _nObj.m_nCurPos = 0.0;
        _nObj.m_nObjectId = m_arrEleParts[i]->GetObjectId();
        nModalData_.AddMoveObj(_nObj);
    }
}

void ArrayValueDeleteDrawingWidget::ResetAllParts()
{
    for (int i = 0; i < m_arrParts.GetSize(); i++)
    {
        delete m_arrParts[i];
        m_arrParts[i] = nullptr;
    }

    m_arrParts.DeleteAll();
    m_arrEleParts.DeleteAll();
    m_arrEleBackGroundParts.DeleteAll();
    m_arrEleIndexParts.DeleteAll();
    NDataStruct::DynArray<NModel::Part*> _arrEleAddrParts;
    NModelManager::ModelManager::Instance()->ArrayModelParse(
                NModelManager::ModelManager::GetGeneralArrayModelFilePath(),
                m_arrEleParts,
                m_arrEleBackGroundParts,
                _arrEleAddrParts,
                m_arrEleIndexParts);

    int _nSize = _arrEleAddrParts.GetSize();
    for(int i = 0; i < _nSize; i++)
    {
        delete _arrEleAddrParts[i];
        _arrEleAddrParts[i] = nullptr;
    }

    _arrEleAddrParts.DeleteAll();
    for(int i = 0; i < m_arrEleBackGroundParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleBackGroundParts[i]);
    }

    for(int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleParts[i]);
    }

    for (int i = 0; i < m_arrEleIndexParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleIndexParts[i]);
    }

    emit Reset();
}

void ArrayValueDeleteDrawingWidget::DeleteAtIndex0(bool checked_)
{
    if(m_nState == 1)
    {
        return;
    }

    ResetAllParts();
    AdjustInitialTransform();
    //update();

    // SetDeletaMovePart's Angle And Calculate Its Move Distance
    // Calculate Part's Angle And DeltaLength
    double _nDeltaLength = 0.0;
    double _nLen1 = 200.0;
    int _nIndex = 0;
    NParameter::ArrayParameter *_pParam = NParameter::ArrayParameter::GetGeneralParameter();
    double _nLen2 = _pParam->m_nElementSize.m_nWidth * _nIndex;
    _nDeltaLength = sqrt(_nLen1*_nLen1+_nLen2*_nLen2);
    double _nAngle = asin(_nLen1/_nDeltaLength);
    double _nDeletePartMoveAngle = _nAngle / PI * 180.0 + 180.0;
    NModel::MovablePart* _pMovePart = (NModel::MovablePart*)m_arrEleParts[_nIndex];
    NModel::Position _nPos = _pMovePart->GetPosition();
    _nPos.m_nPosition.m_nLinearPos.m_nAngle = _nDeletePartMoveAngle;
    _pMovePart->SetPosition(_nPos);
    m_nKeyAllocator.Reset();
    // For Every Part Allocator a Unique Id
    // to Unique Identify every part and to speed up matching
    for (int i = 0; i < m_arrParts.GetSize(); i++)
    {
        int _nUniqueId = m_nKeyAllocator.Allocate();
        m_arrParts[i]->SetObjectId(_nUniqueId);
        m_nKeyAllocator.Register(_nUniqueId, m_arrParts[i]);
    }

    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NFileParse::ArrayModalData _nModalData;
    GetModalParameter(_nModalData);

    // step1:
    // generate nc file
    GenerateDeleteFile(0, _nDeltaLength);
    //m_arrParts.Add(m_pScalePart);
    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralArrayDeleteFile(0),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);


    // OutPut All Part's Info For Debug
    // For Debug
    QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"del0_show_test");
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

void ArrayValueDeleteDrawingWidget::DeleteAtIndex2(bool checked_)
{
    if(m_nState == 1)
    {
        return;
    }

    ResetAllParts();
    AdjustInitialTransform();
    //update();

    // SetDeletaMovePart's Angle And Calculate Its Move Distance
    // Calculate Part's Angle And DeltaLength
    double _nDeltaLength = 0.0;
    double _nLen1 = 200.0;
    int _nIndex = 2;
    NParameter::ArrayParameter *_pParam = NParameter::ArrayParameter::GetGeneralParameter();
    double _nLen2 = _pParam->m_nElementSize.m_nWidth * _nIndex;
    _nDeltaLength = sqrt(_nLen1*_nLen1+_nLen2*_nLen2);
    double _nAngle = asin(_nLen1/_nDeltaLength);
    double _nDeletePartMoveAngle = _nAngle / PI * 180.0 + 180.0;
    NModel::MovablePart* _pMovePart = (NModel::MovablePart*)m_arrEleParts[_nIndex];
    NModel::Position _nPos = _pMovePart->GetPosition();
    _nPos.m_nPosition.m_nLinearPos.m_nAngle = _nDeletePartMoveAngle;
    _pMovePart->SetPosition(_nPos);
    m_nKeyAllocator.Reset();
    // For Every Part Allocator a Unique Id
    // to Unique Identify every part and to speed up matching
    for (int i = 0; i < m_arrParts.GetSize(); i++)
    {
        int _nUniqueId = m_nKeyAllocator.Allocate();
        m_arrParts[i]->SetObjectId(_nUniqueId);
        m_nKeyAllocator.Register(_nUniqueId, m_arrParts[i]);
    }

    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NFileParse::ArrayModalData _nModalData;
    GetModalParameter(_nModalData);

    // step1:
    // generate nc file
    GenerateDeleteFile(_nIndex, _nDeltaLength);
    //m_arrParts.Add(m_pScalePart);
    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralArrayDeleteFile(_nIndex),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);


    // OutPut All Part's Info For Debug
    // For Debug
    QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"del2_show_test");
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

void ArrayValueDeleteDrawingWidget::DeleteAtIndex4(bool checked_)
{
    if(m_nState == 1)
    {
        return;
    }

    ResetAllParts();
    AdjustInitialTransform();
    //update();

    // SetDeletaMovePart's Angle And Calculate Its Move Distance
    // Calculate Part's Angle And DeltaLength
    double _nDeltaLength = 0.0;
    double _nLen1 = 200.0;
    int _nIndex = 4;
    NParameter::ArrayParameter *_pParam = NParameter::ArrayParameter::GetGeneralParameter();
    double _nLen2 = _pParam->m_nElementSize.m_nWidth * _nIndex;
    _nDeltaLength = sqrt(_nLen1*_nLen1+_nLen2*_nLen2);
    double _nAngle = asin(_nLen1/_nDeltaLength);
    double _nDeletePartMoveAngle = _nAngle / PI * 180.0 + 180.0;
    NModel::MovablePart* _pMovePart = (NModel::MovablePart*)m_arrEleParts[_nIndex];
    NModel::Position _nPos = _pMovePart->GetPosition();
    _nPos.m_nPosition.m_nLinearPos.m_nAngle = _nDeletePartMoveAngle;
    _pMovePart->SetPosition(_nPos);
    m_nKeyAllocator.Reset();
    // For Every Part Allocator a Unique Id
    // to Unique Identify every part and to speed up matching
    for (int i = 0; i < m_arrParts.GetSize(); i++)
    {
        int _nUniqueId = m_nKeyAllocator.Allocate();
        m_arrParts[i]->SetObjectId(_nUniqueId);
        m_nKeyAllocator.Register(_nUniqueId, m_arrParts[i]);
    }

    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NFileParse::ArrayModalData _nModalData;
    GetModalParameter(_nModalData);

    // step1:
    // generate nc file
    GenerateDeleteFile(_nIndex, _nDeltaLength);
    //m_arrParts.Add(m_pScalePart);
    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralArrayDeleteFile(_nIndex),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);

    // OutPut All Part's Info For Debug
    // For Debug
    QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"del5_show_test");
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

void ArrayValueDeleteDrawingWidget::GenerateDeleteFile(
    int nIndex_,
    double nDeltaLength_)
{
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NNcManager::NcManager::Instance()->GeneralArrayDeleteFileGenerate(
                nIndex_,
                nDeltaLength_,
                _nArrNcParam);
}
