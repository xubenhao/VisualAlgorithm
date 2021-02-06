//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "arrayvalueinsertdrawingwidget.h"

ArrayValueInsertDrawingWidget::ArrayValueInsertDrawingWidget(QWidget *parent) : QWidget(parent)
{
    Initialize();
    m_nState = -1;
}

NModel::Part* ArrayValueInsertDrawingWidget::ConstructInsertElement(
        char* pContent_,
        int nIndex_,
        double& nDeltaLength_)
{
    // construct a scale part
    NParameter::ArrayParameter *_pParam = NParameter::ArrayParameter::GetGeneralParameter();
    NModel::ArrayPart* _pPart = new NModel::ArrayPart(NModel::ELEMENT);
    NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(
                0.0,
                -200.0,
                _pPart);
    _pPart->SetInitialTransform(_pTrans);

    // Calculate Part's Angle And DeltaLength
    double _nLen1 = 200.0;
    double _nLen2 = _pParam->m_nElementSize.m_nWidth * nIndex_;
    nDeltaLength_ = sqrt(_nLen1*_nLen1+_nLen2*_nLen2);
    double _nAngle = asin(_nLen1/nDeltaLength_);
    NModel::Position _nPos;
    _nPos.m_nMoveType = NModel::MOVE_TYPE::LINEAR;
    _nPos.m_nPosition.m_nLinearPos.m_nAngle = _nAngle / PI * 180.0;
    _nPos.m_nPosition.m_nLinearPos.m_nCurPosition = 0.0;
    _pPart->SetPosition(_nPos);

    NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
    _pDrawing->setParent(_pPart);

    QPen _nPen = NParameter::GetPen(
                _pParam->m_nPen.m_nColor,
                _pParam->m_nPen.m_nWidth);
    QBrush _nBrush;
    _nBrush = NParameter::GetBrush(
                COLOR_6);
    QString _strFamily(_pParam->m_nFont.m_strFamily);
    QFont _nFont(_strFamily, _pParam->m_nFont.m_nPointSize, _pParam->m_nFont.m_nWeight, _pParam->m_nFont.m_bItalic);
    // setting part's pen
    _pDrawing->SetPen(_nPen);
    // setting part's brush
    _pDrawing->SetBrush(_nBrush);
    _pDrawing->SetFont(_nFont);

    NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
    NStruct::Rect _nRect;
    _nRect.SetHeight(_pParam->m_nElementSize.m_nHeight);
    _nRect.SetWeight(_pParam->m_nElementSize.m_nWidth);
    NGeometry::GeometryRect* _pRectGeo = new NGeometry::GeometryRect(_nRect, _pGeoGroup);

    QByteArray _arrByte(pContent_, strlen(pContent_));
    NGeometry::GeometryText* _pTextGeo = new NGeometry::GeometryText(_arrByte, _nRect, Qt::AlignCenter, _pGeoGroup);
    _pGeoGroup->Add(_pRectGeo);
    _pGeoGroup->Add(_pTextGeo);
    _pDrawing->SetGeometry(_pGeoGroup);
    _pPart->SetDrawing(_pDrawing);
    _pPart->SetName(pContent_);
    return _pPart;
}

void ArrayValueInsertDrawingWidget::ResetAllParts()
{
    for(int i = 0; i < m_arrParts.GetSize(); i++)
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
    }

    for(int i = 0; i < m_arrEleBackGroundParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleBackGroundParts[i]);
    }

    for(int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleParts[i]);
    }

    for(int i = 0; i < m_arrEleIndexParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleIndexParts[i]);
    }
}

void ArrayValueInsertDrawingWidget::Initialize()
{
    m_pInsertPart = nullptr;
    m_pService = nullptr;
    ResetAllParts();

    m_pService = new NAnimationService::AnimationService(this);
    m_nRefreshTimerId = startTimer(20);
}

void ArrayValueInsertDrawingWidget::timerEvent(QTimerEvent *event)
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

void ArrayValueInsertDrawingWidget::AdjustInitialTransform()
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

void ArrayValueInsertDrawingWidget::ProcessNcShow(NNcShow::NcShow* pShow_)
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

QImage ArrayValueInsertDrawingWidget::GetImage()
{
    if(m_nState == 1)
    {
        return m_nImage;
    }
    else
    {
        QImage image = QImage(this ->size(), QImage::Format_RGB32);
        image.fill(Qt::white);

        int _nSize = m_arrParts.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            m_arrParts[i]->Draw(&image);
        }

        return image;
    }
}

void ArrayValueInsertDrawingWidget::paintEvent(QPaintEvent* event)
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

void ArrayValueInsertDrawingWidget::GetArrayParameter(NParameter::ArrayNcParameter& nArrNcParam_)
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

void ArrayValueInsertDrawingWidget::GetModalParameter(NFileParse::ArrayModalData& nModalData_)
{
    for (int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        NFileParse::MoveObj _nObj;
        strncpy(_nObj.m_strObjName, m_arrEleParts[i]->GetName(), sizeof(_nObj.m_strObjName));
        _nObj.m_nCurPos = 0.0;
        _nObj.m_nObjectId = m_arrEleParts[i]->GetObjectId();
        nModalData_.AddMoveObj(_nObj);
    }

    if(m_pInsertPart)
    {
        NFileParse::MoveObj _nObj;
        strncpy(_nObj.m_strObjName, m_pInsertPart->GetName(), sizeof(_nObj.m_strObjName));
        _nObj.m_nCurPos = 0.0;
        _nObj.m_nObjectId = m_pInsertPart->GetObjectId();
        nModalData_.AddMoveObj(_nObj);
    }
}

void ArrayValueInsertDrawingWidget::Insert10AtIndex2(bool checked_)
{
    if(m_nState == 1)
    {
        return;
    }

    ResetAllParts();
    double _nDelta = 0.0;
    m_pInsertPart = ConstructInsertElement((char*)"10", 2, _nDelta);
    if(m_pInsertPart)
    {
        m_arrParts.Add(m_pInsertPart);
    }

    AdjustInitialTransform();
    //update();

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
    GenerateInsertFile(
        (char*)"10",
        2,
        _nDelta,
        m_pInsertPart->GetObjectId());
    //m_arrParts.Add(m_pScalePart);
    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralArrayInsertFile((char*)"10", 2),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);

    // OutPut All Part's Info For Debug
    // For Debug
    QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"I10_show_test");
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

void ArrayValueInsertDrawingWidget::Insert11AtIndex5(bool checked_)
{
    if(m_nState == 1)
    {
        return;
    }

    ResetAllParts();
    double _nDelta = 0.0;
    m_pInsertPart = ConstructInsertElement((char*)"11", 5, _nDelta);
    if(m_pInsertPart)
    {
        m_arrParts.Add(m_pInsertPart);
    }

    AdjustInitialTransform();
    //update();

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
    GenerateInsertFile(
        (char*)"11",
        5,
        _nDelta,
        m_pInsertPart->GetObjectId());
    //m_arrParts.Add(m_pScalePart);
    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralArrayInsertFile((char*)"11", 5),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);


    // OutPut All Part's Info For Debug
    // For Debug
    QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"I11_show_test");
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

void ArrayValueInsertDrawingWidget::GenerateInsertFile(
    char *pValue_,
    int nIndex_,
    double nDeltaLength_,
    long nInsertObjId_)
{
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NNcManager::NcManager::Instance()->GeneralArrayInsertFileGenerate(
                pValue_,
                nIndex_,
                nDeltaLength_,
                _nArrNcParam,
                nInsertObjId_);
}
