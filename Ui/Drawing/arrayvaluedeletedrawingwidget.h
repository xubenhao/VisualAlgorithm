//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYVALUEDELETEDRAWINGWIDGET_H
#define APP_UI_ARRAYVALUEDELETEDRAWINGWIDGET_H

#include "Ui/header.h"

class ArrayValueDeleteDrawingWidget : public QWidget
{
   Q_OBJECT
public:
    explicit ArrayValueDeleteDrawingWidget(QWidget *parent = nullptr);
    void Initialize();
    virtual void timerEvent(QTimerEvent *event);
protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

public:
    void DeleteAtIndex0(bool checked_);
    void DeleteAtIndex2(bool checked_);
    void DeleteAtIndex4(bool checked_);
    void ProcessNcShow(NNcShow::NcShow* pShow_);

Q_SIGNALS:
    void Reset();
    void ProcessTip(NNcShow::NcShowTip* pNcShow_);

private:
    void GenerateDeleteFile(
        int nIndex_,
        double nDeltaLength_);
    //void Generate7SearchFile();
    //void ConstructScalePart();
    void AdjustInitialTransform();
    QImage GetImage();
    void GetArrayParameter(NParameter::ArrayNcParameter& nArrNcParam_);
    void GetModalParameter(NFileParse::ArrayModalData& nModalData_);
    void ResetAllParts();
    NModel::Part* ConstructInsertElement(
            char* pContent_,
            int nIndex_,
            double& nDeltaLength_);

private:
    NDataStruct::DynArray<NModel::Part*> m_arrEleParts;
    NDataStruct::DynArray<NModel::Part*> m_arrEleBackGroundParts;
    NDataStruct::DynArray<NModel::Part*> m_arrEleIndexParts;
    //NModel::Part* m_pInsertPart;
    NDataStruct::DynArray<NModel::Part*> m_arrParts;
    NAnimationService::AnimationService *m_pService;
    int m_nRefreshTimerId;
    NDataStruct::KeyAllocator<NModel::Part*> m_nKeyAllocator;
private:
    QImage m_nImage;
    int m_nState;

};

#endif // ARRAYVALUEDELETEDRAWINGWIDGET_H
