//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYVALUEVISITDRAWINGWIDGET_H
#define APP_UI_ARRAYVALUEVISITDRAWINGWIDGET_H

#include "Ui/header.h"

class ArrayValueVisitDrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ArrayValueVisitDrawingWidget(QWidget *parent = nullptr);
    void Initialize();
    virtual void timerEvent(QTimerEvent *event);
protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void ResetAllPart();
public:
    void Search4Clicked(bool checked_);
    void Search7Clicked(bool checked_);
    void ProcessNcShow(NNcShow::NcShow* pShow_);

Q_SIGNALS:
    void Reset();
    void ProcessTip(NNcShow::NcShowTip* pNcShow_);

private:
    void Generate4SearchFile();
    void Generate7SearchFile();
    void ConstructScalePart();
    void AdjustInitialTransform();
    QImage GetImage();
    void GetArrayParameter(NParameter::ArrayNcParameter& nArrNcParam_);
    void GetModalParameter(NFileParse::ArrayModalData& nModalData_);
    void ResetAllParts();

private:
    NDataStruct::DynArray<NModel::Part*> m_arrEleParts;
    NDataStruct::DynArray<NModel::Part*> m_arrEleBackGroundParts;
    NModel::Part* m_pScalePart;


    NDataStruct::DynArray<NModel::Part*> m_arrParts;
    NAnimationService::AnimationService *m_pService;
    int m_nRefreshTimerId;
private:
    QImage m_nImage;
    int m_nState;
    NDataStruct::KeyAllocator<NModel::Part*> m_nKeyAllocator;
};

#endif // ARRAYVALUEVISITDRAWINGWIDGET_H
