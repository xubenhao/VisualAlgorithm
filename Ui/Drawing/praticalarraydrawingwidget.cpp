//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "praticalarraydrawingwidget.h"

PraticalArrayDrawingWidget::PraticalArrayDrawingWidget(QWidget *parent) : QWidget(parent)
{
    Initialize();
}

void PraticalArrayDrawingWidget::Initialize()
{
    m_nState = -1;
    m_pInsertPart = nullptr;
    m_nId = -1;
    m_pScalePart = nullptr;
    m_pService = new NAnimationService::AnimationService(this);
    m_nRefreshTimerId = startTimer(20);
}

void PraticalArrayDrawingWidget::ResetAllParts()
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
    m_pScalePart = nullptr;
    m_pInsertPart = nullptr;

    if(m_nModelParam.m_nCapacity <= 0)
    {
        return;
    }

    // Get part models from model file
    NDataStruct::DynArray<NModel::Part*> _arrEleAddrParts;
    NFileParse::ArrayModelFileParse* _pArrayParse = new NFileParse::ArrayModelFileParse(this);
    _pArrayParse->BuildModel(
                m_nModelParam,
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

void PraticalArrayDrawingWidget::AdjustInitialTransform()
{
    // Adjust Part's Initial Transform when first show in client of window
    // to let them more preporty in place

    QRect _rc = this->rect();
    double _nLeftX = (_rc.width()
                      - m_nModelParam.m_nCapacity * m_nModelParam.m_nElementSize.m_nWidth) / 2.0;
    double _nLeftY = (-_rc.height()
                      + m_nModelParam.m_nElementSize.m_nHeight) / 2.0 + 40;
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

void PraticalArrayDrawingWidget::LoadModelFile(QString strFile_)
{
    NFileParse::ArrayModelFileParse* _pArrayParse = new NFileParse::ArrayModelFileParse(nullptr);
    _pArrayParse->ParseFile(
            strFile_,
            m_nModelParam);
    delete _pArrayParse;
}

void PraticalArrayDrawingWidget::SaveModelFile(QString strFile_)
{
    NFileGenerate::ArrayModelFileGenerate* _pFileGen = new NFileGenerate::ArrayModelFileGenerate();
    _pFileGen->SetParameter(m_nModelParam);
    _pFileGen->Generate(strFile_);
}

void PraticalArrayDrawingWidget::Load(int nId_, int nCapacity_)
{
    QString _strFile = NModelManager::ModelManager::GetPraticalArrayModelFilePath(nId_, nCapacity_);
    if(QFile::exists(_strFile))
    {
        LoadModelFile(_strFile);
    }
    else
    {
        NParameter::ArrayParameter::GetPraticalParameter(
            nCapacity_,
            m_nModelParam);
    }
}

void PraticalArrayDrawingWidget::Save()
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
    m_pScalePart = nullptr;


    QString _strFile = NModelManager::ModelManager::GetPraticalArrayModelFilePath(
                m_nId,
                m_nModelParam.m_nCapacity);
    SaveModelFile(_strFile);
}

void PraticalArrayDrawingWidget::ResetShow(
        int nId_,
        int nCapacity_)
{
    if(m_nState == 1)
    {
        return;
    }

    m_nId = nId_;
    Load(nId_, nCapacity_);
    ResetAllParts();
    AdjustInitialTransform();

    // we now know capacity/size/names
    NDataStruct::DynArray<QString> _arrValues;
    for(int i = 0; i < m_nModelParam.m_nSize; i++)
    {
        _arrValues.Add(QString(m_nModelParam.m_arrElements[i].m_nContent));
    }

    emit Sync(
       m_nModelParam.m_nSize,
       _arrValues);
}

void PraticalArrayDrawingWidget::timerEvent(QTimerEvent *event)
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

void PraticalArrayDrawingWidget::ProcessNcShow(NNcShow::NcShow* pShow_)
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
        if(strcmp(_pTip->GetTip(), "Finish") == 0)
        {
            if(m_nFinishCallBack)
            {
                m_nFinishCallBack();
            }
        }

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

QImage PraticalArrayDrawingWidget::GetImage()
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

void PraticalArrayDrawingWidget::paintEvent(QPaintEvent* event)
{
    // doing a linear transform let parts show in center at first show
    /*static bool _bFlag = false;
    if(_bFlag == false)
    {
        _bFlag = true;
        AdjustInitialTransform();
    }*/

    Q_UNUSED(event);
    QPainter painter(this);
    QImage image = GetImage();
    painter.drawImage(rect(), image, image.rect());
}

void PraticalArrayDrawingWidget::GetArrayParameter(NParameter::ArrayNcParameter& nArrNcParam_)
{
    // we need know the capacity,the size
    //nArrNcParam_.m_nSize = m_nSize;
    //nArrNcParam_.m_nCapacity = m_nCapacity;
    //nArrNcParam_.m_arrElements = m_arrElements;
    //NParameter::ArrayNcParameter _nArrNcParam;
    nArrNcParam_.m_nSize = m_nModelParam.m_nSize;
    nArrNcParam_.m_nCapacity = m_nModelParam.m_nCapacity;
    for (int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        NParameter::ArrayNcElement _nEle;
        _nEle.m_nSize = m_nModelParam.m_nElementSize;
        _nEle.m_nDefault = m_nModelParam.m_arrElements[i].m_nBrush.m_nColor;
        _nEle.m_nMatch = COLOR_11;
        _nEle.m_nNotMatch = COLOR_10;
        strncpy(
            _nEle.m_strContent,
            m_nModelParam.m_arrElements[i].m_nContent,
            sizeof(_nEle.m_strContent));
        strncpy(
            _nEle.m_strName,
            m_nModelParam.m_arrElements[i].m_strName,
            sizeof(_nEle.m_strName));
        _nEle.m_nObjectId = m_arrEleParts[i]->GetObjectId();
        nArrNcParam_.m_arrElements.Add(_nEle);
    }

    if(m_pScalePart)
    {
        strncpy(
            nArrNcParam_.m_strScaleName,
            m_pScalePart->GetName(),
            sizeof(nArrNcParam_.m_strScaleName));
        nArrNcParam_.m_nScaleId = m_pScalePart->GetObjectId();
    }

    nArrNcParam_.m_nDefToFirstLen = 100.0;
    nArrNcParam_.m_nDefToFirstAngle = 90.0;
}

// according to different context
// it should return different value
void PraticalArrayDrawingWidget::GetModalParameter(NFileParse::ArrayModalData& nModalData_)
{
    for (int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        NFileParse::MoveObj _nObj;
        strncpy(
            _nObj.m_strObjName,
            m_arrEleParts[i]->GetName(),
            sizeof(_nObj.m_strObjName));
        _nObj.m_nCurPos = 0.0;
        _nObj.m_nObjectId = m_arrEleParts[i]->GetObjectId();
        nModalData_.AddMoveObj(_nObj);
    }

    if(m_pInsertPart)
    {
        NFileParse::MoveObj _nObj;
        strncpy(
            _nObj.m_strObjName,
            m_pInsertPart->GetName(),
            sizeof(_nObj.m_strObjName));
        _nObj.m_nCurPos = 0.0;
        _nObj.m_nObjectId = m_pInsertPart->GetObjectId();
        nModalData_.AddMoveObj(_nObj);
    }

    if(m_pScalePart)
    {
        NFileParse::MoveObj _nObj;
        strncpy(
            _nObj.m_strObjName,
            m_pScalePart->GetName(),
            sizeof(_nObj.m_strObjName));
        _nObj.m_nCurPos = 0.0;
        _nObj.m_nObjectId = m_pScalePart->GetObjectId();
        nModalData_.AddMoveObj(_nObj);
    }
}

NModel::Part* PraticalArrayDrawingWidget::ConstructInsertElement(
        QString strValue_,
        int nIndex_,
        double& nDeltaLength_)
{
    // construct a scale part
    //NParameter::ArrayParameter *_pParam = NParameter::ArrayParameter::GetGeneralParameter();
    NModel::ArrayPart* _pPart = new NModel::ArrayPart(NModel::ELEMENT);
    NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(
                0.0,
                -200.0,
                _pPart);
    _pPart->SetInitialTransform(_pTrans);

    // Calculate Part's Angle And DeltaLength
    double _nLen1 = 200.0;
    double _nLen2 = m_nModelParam.m_nElementSize.m_nWidth * nIndex_;
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
                COLOR_9,
                10.0);
    QBrush _nBrush;
    COLOR _arrColors[10] =
    {
        COLOR_0,
        COLOR_1,
        COLOR_2,
        COLOR_3,
        COLOR_4,

        COLOR_5,
        COLOR_6,
        COLOR_7,
        COLOR_8,
        COLOR_9,
    };

    _nBrush = NParameter::GetBrush(
                _arrColors[m_nModelParam.m_nSize % 10]);
    NParameter::Font _nFont;
    QString _strFamily(_nFont.m_strFamily);
    QFont _nQFont(
        _strFamily,
        _nFont.m_nPointSize,
        _nFont.m_nWeight,
        _nFont.m_bItalic);
    // setting part's pen
    _pDrawing->SetPen(_nPen);
    // setting part's brush
    _pDrawing->SetBrush(_nBrush);
    _pDrawing->SetFont(_nQFont);

    NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
    NStruct::Rect _nRect;
    _nRect.SetHeight(m_nModelParam.m_nElementSize.m_nHeight);
    _nRect.SetWeight(m_nModelParam.m_nElementSize.m_nWidth);
    NGeometry::GeometryRect* _pRectGeo = new NGeometry::GeometryRect(
        _nRect,
        _pGeoGroup);
    QByteArray _arrByte(strValue_.toUtf8());
    NGeometry::GeometryText* _pTextGeo = new NGeometry::GeometryText(
        _arrByte,
        _nRect,
        Qt::AlignCenter,
        _pGeoGroup);
    _pGeoGroup->Add(_pRectGeo);
    _pGeoGroup->Add(_pTextGeo);
    _pDrawing->SetGeometry(_pGeoGroup);
    _pPart->SetDrawing(_pDrawing);

    // Adjust
    QRect _rc = this->rect();
    double _nLeftX = (_rc.width()
                      - m_nModelParam.m_nCapacity * m_nModelParam.m_nElementSize.m_nWidth) / 2.0;
    double _nLeftY = (-_rc.height()
                      + m_nModelParam.m_nElementSize.m_nHeight) / 2.0 + 40;
    _pTrans = new NTransform::LinearTransform(_nLeftX, _nLeftY);
    NTransform::Transform* _pIniTrans = _pPart->GetInitialTransform();
    NTransform::TransformGroup* _pGroupTrans = new NTransform::TransformGroup(_pPart);
    if(_pIniTrans)
    {
        _pGroupTrans->Add(_pIniTrans);
        _pIniTrans->setParent(_pGroupTrans);
    }

    NTransform::Transform* _pTemp = _pTrans->DeepCopy();
    _pGroupTrans->Add(_pTemp);
    _pTemp->setParent(_pGroupTrans);
    _pPart->SetInitialTransform(_pGroupTrans);

    delete  _pTrans;

    NParameter::Element _nInsertElement;
    strncpy(_nInsertElement.m_nContent, strValue_.toUtf8().data(), sizeof(_nInsertElement.m_nContent));
    _nInsertElement.m_nBrush.m_nColor = _arrColors[m_nModelParam.m_nSize % 10];
    _nInsertElement.m_nPen.m_nColor = COLOR_9;
    _nInsertElement.m_nPen.m_nWidth = 10.0;
    m_nFinishCallBack = std::bind(
                &PraticalArrayDrawingWidget::InsertCallback,
                this,
                _nInsertElement,
                nIndex_);
    return _pPart;
}

void PraticalArrayDrawingWidget::InsertCallback(
   const NParameter::Element& nEle_,
   int nIndex_)
{
    // Test
    //m_nModelParam.m_arrElements.DeleteAll();
    m_nModelParam.m_arrElements.Insert(nIndex_, nEle_);
    //NModel::ArrayPart* _pPart = (NModel::ArrayPart*)m_pInsertPart;
    //NModel::Position _nPos;
    //_pPart->SetPosition(_nPos);
    //m_arrEleParts.Insert(nIndex_, m_pInsertPart);
    //m_pInsertPart = nullptr;
    m_nModelParam.m_nSize++;
}

void PraticalArrayDrawingWidget::DeleteCallback(
   int nIndex_)
{
    // Test
    //m_nModelParam.m_arrElements.DeleteAll();
    m_nModelParam.m_arrElements.DeleteByIndex(nIndex_);
    m_nModelParam.m_nSize--;
}

void PraticalArrayDrawingWidget::SearchValueCallback()
{
    //
}

void PraticalArrayDrawingWidget::GenerateInsertFile(
    const QString& strValue_,// Insert object content
    int nIndex_,// insert pos
    double nDeltaLength_,// insert object move distance
    long nInsertObjId_)// insert object id
{
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    // generate nc file
    NNcManager::NcManager::Instance()->GeneralPraticalArrayInsertFileGenerate(
                strValue_.toUtf8().data(),// insert object's content
                nIndex_,// insert pos
                nDeltaLength_,// insert object move distance
                _nArrNcParam,//
                nInsertObjId_);// insert object's id
}

void PraticalArrayDrawingWidget::Insert(int nIndex_, QString strValue_)
{
    if(m_nState == 1)
    {
        return;
    }

    if(nIndex_ < 0 || nIndex_ > m_nModelParam.m_nSize)
    {
        return;
    }

    ResetAllParts();
    AdjustInitialTransform();
    double _nDelta = 0.0;
    m_pInsertPart = ConstructInsertElement(
        strValue_,
        nIndex_,
        _nDelta);

    if(m_pInsertPart)
    {
        m_arrParts.Add(m_pInsertPart);
    }

    //update();
    // insert part need adjust
    m_nKeyAllocator.Reset();
    for(int i = 0; i < m_arrParts.GetSize(); i++)
    {
        int _nUniqueId = m_nKeyAllocator.Allocate();
        m_arrParts[i]->SetObjectId(_nUniqueId);
        m_nKeyAllocator.Register(_nUniqueId, m_arrParts[i]);
    }

    //return;
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NFileParse::ArrayModalData _nModalData;
    GetModalParameter(_nModalData);

    // step1:
    // generate nc file
    GenerateInsertFile(
        strValue_,
        nIndex_,
        _nDelta,
        m_pInsertPart->GetObjectId());

    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralPraticalArrayInsertFile(
                    strValue_.toUtf8().data(),
                    nIndex_),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);
}

void PraticalArrayDrawingWidget::Delete(int nIndex_)
{
    if(m_nState == 1)
    {
        return;
    }

    if(nIndex_ < 0
        || nIndex_ >= m_nModelParam.m_nSize)
    {
        return;
    }

    ResetAllParts();
    AdjustInitialTransform();

    // SetDeletaMovePart's Angle And Calculate Its Move Distance
    // Calculate Part's Angle And DeltaLength
    double _nDeltaLength = 0.0;
    double _nLen1 = 200.0;

    double _nLen2 = m_nModelParam.m_nElementSize.m_nWidth * nIndex_;
    _nDeltaLength = sqrt(_nLen1*_nLen1+_nLen2*_nLen2);
    double _nAngle = asin(_nLen1/_nDeltaLength);
    double _nDeletePartMoveAngle = _nAngle / PI * 180.0 + 180.0;
    NModel::MovablePart* _pMovePart = (NModel::MovablePart*)m_arrEleParts[nIndex_];
    NModel::Position _nPos = _pMovePart->GetPosition();
    _nPos.m_nPosition.m_nLinearPos.m_nAngle = _nDeletePartMoveAngle;
    _pMovePart->SetPosition(_nPos);

    m_nFinishCallBack = std::bind(
                &PraticalArrayDrawingWidget::DeleteCallback,
                this,
                nIndex_);
    //update();
    // insert part need adjust
    m_nKeyAllocator.Reset();
    for(int i = 0; i < m_arrParts.GetSize(); i++)
    {
        int _nUniqueId = m_nKeyAllocator.Allocate();
        m_arrParts[i]->SetObjectId(_nUniqueId);
        m_nKeyAllocator.Register(_nUniqueId, m_arrParts[i]);
    }

    //return;
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NFileParse::ArrayModalData _nModalData;
    GetModalParameter(_nModalData);

    // step1:
    // generate nc file
    // step1:
    // generate nc file
    GenerateDeleteFile(
        nIndex_,
        _nDeltaLength);

    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralPraticalArrayDeleteFile(nIndex_),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);
}

void PraticalArrayDrawingWidget::SearchByValue(QString strValue_)
{
    if(m_nState == 1)
    {
        return;
    }

    ResetAllParts();
    m_pScalePart = ConstructScalePart();
    m_arrParts.Add(m_pScalePart);

    AdjustInitialTransform();

    // insert part need adjust
    m_nKeyAllocator.Reset();
    for(int i = 0; i < m_arrParts.GetSize(); i++)
    {
        int _nUniqueId = m_nKeyAllocator.Allocate();
        m_arrParts[i]->SetObjectId(_nUniqueId);
        m_nKeyAllocator.Register(_nUniqueId, m_arrParts[i]);
    }

    m_nFinishCallBack = nullptr;
    //return;
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NFileParse::ArrayModalData _nModalData;
    GetModalParameter(_nModalData);

    // step1:
    // generate nc file
    GenerateSearchFile(strValue_);
    //
    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralPraticalArraySearchFile(strValue_.toUtf8().data()),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);
}

NModel::Part* PraticalArrayDrawingWidget::ConstructScalePart()
{
    NModel::ArrayPart* _pPart = new NModel::ArrayPart(NModel::ELEMENT_SCALE);
    NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(
                m_nModelParam.m_nElementSize.m_nWidth/2.0,
                -m_nModelParam.m_nElementSize.m_nHeight - 10.0,
                _pPart);
    _pPart->SetInitialTransform(_pTrans);
    NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
    _pDrawing->setParent(_pPart);

    QPen _nPen = NParameter::GetPen(
        m_nModelParam.m_nPen.m_nColor,
        m_nModelParam.m_nPen.m_nWidth);
    QBrush _nBrush;
    _nBrush = NParameter::GetBrush(m_nModelParam.m_nBrush.m_nColor);
    QString _strFamily(m_nModelParam.m_nFont.m_strFamily);
    QFont _nFont(
        _strFamily,
        m_nModelParam.m_nFont.m_nPointSize,
        m_nModelParam.m_nFont.m_nWeight,
        m_nModelParam.m_nFont.m_bItalic);
    // setting part's pen
    _pDrawing->SetPen(_nPen);
    // setting part's brush
    _pDrawing->SetBrush(_nBrush);
    _pDrawing->SetFont(_nFont);

    NGeometry::GeometryGroup* _pGeoGroup = new NGeometry::GeometryGroup(_pDrawing);
    //NStruct::Rect _nRect;
    //_nRect.SetHeight(nParam_.m_nElementSize.m_nHeight);
    //_nRect.SetWeight(nParam_.m_nElementSize.m_nWidth);
    NStruct::Line _nLine;
    double _nAngle = (180.0 + 45.0) / 180.0 * PI;
    _nLine.SetStart(NStruct::Point(10 *  cos(_nAngle), 10 * sin(_nAngle)));
    _nLine.SetEnd(NStruct::Point());
    NGeometry::GeometryLine* _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
    _pGeoGroup->Add(_pLineGeo);
    _nAngle = (270.0 + 45.0) / 180.0 * PI;
    _nLine.SetStart(NStruct::Point(10*  cos(_nAngle), 10 * sin(_nAngle)));
    _nLine.SetEnd(NStruct::Point());
    _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
    _pGeoGroup->Add(_pLineGeo);

    _nLine.SetStart(NStruct::Point());
    _nLine.SetEnd(NStruct::Point(0.0, -30.0));
    _pLineGeo = new NGeometry::GeometryLine(_nLine, _pGeoGroup);
    _pGeoGroup->Add(_pLineGeo);
    _pDrawing->SetGeometry(_pGeoGroup);

    _pPart->SetDrawing(_pDrawing);
    return _pPart;
}

void PraticalArrayDrawingWidget::SearchByIndex(int nIndex_)
{

}

/*
IndexSearch
ValueSearch
InsertByIndex
DeleteByIndex
*/
/*void PraticalArrayDrawingWidget::Delete(int nIndex_)
{
    /*if(m_nState == 1)
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
}*/

void PraticalArrayDrawingWidget::GenerateSearchFile(
    const QString& strValue_)
{
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NNcManager::NcManager::Instance()->GeneralPraticalArraySearchFileGenerate(
                strValue_.toUtf8().data(),
                _nArrNcParam);
}

/*
    Genenerate different file
    according to different use
*/
void PraticalArrayDrawingWidget::GenerateDeleteFile(
    int nIndex_,
    double nDeltaLength_)
{
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NNcManager::NcManager::Instance()->GeneralPraticalArrayDeleteFileGenerate(
                nIndex_,
                nDeltaLength_,
                _nArrNcParam);
}
