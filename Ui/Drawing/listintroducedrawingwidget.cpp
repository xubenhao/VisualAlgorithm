//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "listintroducedrawingwidget.h"

ListIntroduceDrawingWidget::ListIntroduceDrawingWidget(QWidget *parent) : QWidget(parent)
{
    Initialize();
    m_nState = -1;
}

void ListIntroduceDrawingWidget::ConstructScalePart()
{
    // construct a scale part
    NParameter::ArrayParameter *_pParam = NParameter::ArrayParameter::GetGeneralParameter();
    NModel::ArrayPart* _pPart = new NModel::ArrayPart(NModel::ELEMENT_SCALE);
    NTransform::LinearTransform* _pTrans = new NTransform::LinearTransform(
                _pParam->m_nElementSize.m_nWidth/2.0,
                -_pParam->m_nElementSize.m_nHeight - 10.0,
                _pPart);
    _pPart->SetInitialTransform(_pTrans);
    NDrawing::Drawing* _pDrawing = new NDrawing::Drawing(_pPart);
    _pDrawing->setParent(_pPart);

    QPen _nPen = NParameter::GetPen(_pParam->m_nPen.m_nColor, _pParam->m_nPen.m_nWidth);
    QBrush _nBrush;
    _nBrush = NParameter::GetBrush(_pParam->m_nBrush.m_nColor);
    QString _strFamily(_pParam->m_nFont.m_strFamily);
    QFont _nFont(_strFamily, _pParam->m_nFont.m_nPointSize, _pParam->m_nFont.m_nWeight, _pParam->m_nFont.m_bItalic);
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
    m_pScalePart = _pPart;
}

void ListIntroduceDrawingWidget::ResetAllParts()
{
    for(int i = 0; i < m_arrParts.GetSize(); i++)
    {
        delete m_arrParts[i];
        m_arrParts[i] = nullptr;
    }

    m_arrParts.DeleteAll();

    /*m_arrEleParts.DeleteAll();
    m_arrEleBackGroundParts.DeleteAll();
    m_pScalePart = nullptr;

    NDataStruct::DynArray<NModel::Part*> _arrEleAddrParts;
    NDataStruct::DynArray<NModel::Part*> _arrEleIndexParts;
    NModelManager::ModelManager::Instance()->ArrayModelParse(
                NModelManager::ModelManager::GetGeneralArrayModelFilePath(),
                m_arrEleParts,
                m_arrEleBackGroundParts,
                _arrEleAddrParts,
                _arrEleIndexParts);

    for(int i = 0; i < m_arrEleBackGroundParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleBackGroundParts[i]);
    }

    for(int i = 0; i < m_arrEleParts.GetSize(); i++)
    {
        m_arrParts.Add(m_arrEleParts[i]);
    }

    int _nSize = _arrEleAddrParts.GetSize();
    for(int i = 0; i < _nSize; i++)
    {
        delete _arrEleAddrParts[i];
        _arrEleAddrParts[i] = nullptr;
    }

    _arrEleAddrParts.DeleteAll();
    _nSize = _arrEleIndexParts.GetSize();
    for(int i = 0; i < _nSize; i++)
    {
        delete _arrEleIndexParts[i];
        _arrEleIndexParts[i] = nullptr;
    }

    _arrEleIndexParts.DeleteAll();*/
    ConstructScalePart();
    m_arrParts.Add(m_pScalePart);
}

void ListIntroduceDrawingWidget::Initialize()
{
    m_pService = nullptr;
    m_pScalePart = nullptr;
    m_pService = new NAnimationService::AnimationService(this);
    ResetAllParts();
    m_nRefreshTimerId = startTimer(20);
}

void ListIntroduceDrawingWidget::timerEvent(QTimerEvent *event)
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

void ListIntroduceDrawingWidget::AdjustInitialTransform()
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

void ListIntroduceDrawingWidget::ProcessNcShow(NNcShow::NcShow* pShow_)
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

QImage ListIntroduceDrawingWidget::GetImage()
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

void ListIntroduceDrawingWidget::paintEvent(QPaintEvent* event)
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

void ListIntroduceDrawingWidget::GetArrayParameter(
        NParameter::ArrayNcParameter& nArrNcParam_)
{
    NParameter::ArrayParameter* _pParam = NParameter::ArrayParameter::GetGeneralParameter();
    //NParameter::ArrayNcParameter _nArrNcParam;
    nArrNcParam_.m_nSize = _pParam->m_nSize;
    nArrNcParam_.m_nCapacity = _pParam->m_nCapacity;
    /*for (int i = 0; i < m_arrEleParts.GetSize(); i++)
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

    strncpy(
        nArrNcParam_.m_strScaleName,
        m_pScalePart->GetName(),
        sizeof(nArrNcParam_.m_strScaleName));
    nArrNcParam_.m_nScaleId = m_pScalePart->GetObjectId();
    nArrNcParam_.m_nDefToFirstLen = 100.0;
    nArrNcParam_.m_nDefToFirstAngle = 45.0;*/
}

void ListIntroduceDrawingWidget::GetModalParameter(NFileParse::ArrayModalData& nModalData_)
{
    /*NFileParse::MoveObj _nObj;
    strncpy(_nObj.m_strObjName, m_pScalePart->GetName(), sizeof(_nObj.m_strObjName));
    _nObj.m_nCurPos = 0.0;
    _nObj.m_nObjectId = m_pScalePart->GetObjectId();
    nModalData_.AddMoveObj(_nObj);*/
}

void ListIntroduceDrawingWidget::Search4Clicked(bool checked_)
{
    if(m_nState == 1)
    {
        return;
    }

    // ReSet All Parts To Its Initial State
    ResetAllParts();
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
    Generate4SearchFile();

    //
    m_pService->StartArray(
        NNcManager::NcManager::GetGeneralArraySearchFile((char*)"4"),
        _nArrNcParam,
        _nModalData,
        m_arrParts,
        m_nKeyAllocator,
        this);


    // OutPut All Part's Info For Debug
    // For Debug
    QString _filepath = NNcManager::NcManager::GetGeneralArraySearchFile((char*)"S4_show_test");
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

void ListIntroduceDrawingWidget::Generate4SearchFile()
{
    NParameter::ArrayNcParameter _nArrNcParam;
    GetArrayParameter(_nArrNcParam);
    NNcManager::NcManager::Instance()->GeneralArraySearchFileGenerate(
                (char*)"4",
                _nArrNcParam);
}
