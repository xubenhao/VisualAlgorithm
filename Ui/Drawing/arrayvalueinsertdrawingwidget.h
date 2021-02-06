//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_ARRAYVALUEINSERTDRAWINGWIDGET_H
#define APP_UI_ARRAYVALUEINSERTDRAWINGWIDGET_H

#include "Ui/header.h"

class ArrayValueInsertDrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ArrayValueInsertDrawingWidget(QWidget *parent = nullptr);
    void Initialize();
    virtual void timerEvent(QTimerEvent *event);
protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void ResetAllParts();
public:
    void Insert10AtIndex2(bool checked_);
    void Insert11AtIndex5(bool checked_);
    void ProcessNcShow(NNcShow::NcShow* pShow_);

Q_SIGNALS:
    void Reset();
    void ProcessTip(NNcShow::NcShowTip* pNcShow_);

private:
    void GenerateInsertFile(
        char* pValue_,
        int nIndex_,
        double nDeltaLength_,
        long nInsertObjId_);
    //void Generate7SearchFile();
    //void ConstructScalePart();
    void AdjustInitialTransform();
    QImage GetImage();
    void GetArrayParameter(NParameter::ArrayNcParameter& nArrNcParam_);
    void GetModalParameter(NFileParse::ArrayModalData& nModalData_);
    void ResetAllParts(
            char* pContent_,
            int nIndex_,
            double& nDeltaLength_);
    NModel::Part* ConstructInsertElement(
            char* pContent_,
            int nIndex_,
            double& nDeltaLength_);

private:
    NDataStruct::DynArray<NModel::Part*> m_arrEleParts;
    NDataStruct::DynArray<NModel::Part*> m_arrEleBackGroundParts;

    NDataStruct::DynArray<NModel::Part*> m_arrEleIndexParts;
    NModel::Part* m_pInsertPart;
    NDataStruct::DynArray<NModel::Part*> m_arrParts;
    NAnimationService::AnimationService *m_pService;
    int m_nRefreshTimerId;
    NDataStruct::KeyAllocator<NModel::Part*> m_nKeyAllocator;
private:
    QImage m_nImage;
    int m_nState;
};

#endif // ARRAYVALUEINSERTDRAWINGWIDGET_H
