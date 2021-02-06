//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef APP_UI_PRATICALARRAYDRAWINGWIDGET_H
#define APP_UI_PRATICALARRAYDRAWINGWIDGET_H

#include "Ui/header.h"

class PraticalArrayDrawingWidget : public QWidget
{ 
    Q_OBJECT
public:
     explicit PraticalArrayDrawingWidget(QWidget *parent = nullptr);
     void Initialize();
     virtual void timerEvent(QTimerEvent *event);
     void ResetShow(int nId_, int nCapacity_);
     void Load(int nId_, int nCapacity_);
     void Save();
public:
     void Insert(int nIndex_, QString strValue_);
     void Delete(int nIndex_);
     void SearchByValue(QString strValue_);
     void SearchByIndex(int nIndex_);

protected:
     void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

 public:
     void ProcessNcShow(NNcShow::NcShow* pShow_);
     int GetState(){return m_nState;}

 Q_SIGNALS:
     void Reset();
     void ProcessTip(NNcShow::NcShowTip* pNcShow_);
     void Sync(
        int nSize_,
        const NDataStruct::DynArray<QString>& arrValues_);
 private:
     void LoadModelFile(QString strFile_);
     void SaveModelFile(QString strFile_);
     NModel::Part* ConstructInsertElement(
             QString strValue_,
             int nIndex_,
             double& nDeltaLength_);
     void GenerateInsertFile(
         const QString& strValue_,
         int nIndex_,
         double nDeltaLength_,
         long nInsertObjId_);
     void GenerateDeleteFile(
         int nIndex_,
         double nDeltaLength_);
     void GenerateSearchFile(
         const QString& strValue_);

     void AdjustInitialTransform();
     QImage GetImage();
     void GetArrayParameter(NParameter::ArrayNcParameter& nArrNcParam_);
     void GetModalParameter(NFileParse::ArrayModalData& nModalData_);
     void ResetAllParts();
     NModel::Part* ConstructInsertElement(
             char* pContent_,
             int nIndex_,
             double& nDeltaLength_);
    NModel::Part* ConstructScalePart();

     void InsertCallback(
        const NParameter::Element& nEle_,
        int nIndex_);
     void DeleteCallback(
        int nIndex_);
     void SearchValueCallback();
 private:
     NModel::Part* m_pScalePart;
     NDataStruct::DynArray<NModel::Part*> m_arrEleParts;
     NDataStruct::DynArray<NModel::Part*> m_arrEleBackGroundParts;
     NDataStruct::DynArray<NModel::Part*> m_arrEleIndexParts;

     NDataStruct::DynArray<NModel::Part*> m_arrParts;
     NAnimationService::AnimationService *m_pService;
     int m_nRefreshTimerId;
     NDataStruct::KeyAllocator<NModel::Part*> m_nKeyAllocator;
     NModel::Part* m_pInsertPart;
private:
     QImage m_nImage;
     int m_nState;
     //NParameter::ArrayNcElement m_nNcParam;
     int m_nId;
     std::function<void()> m_nFinishCallBack;
     NParameter::ArrayParameter m_nModelParam;
     //NDataStruct::DynArray<NParameter::ArrayNcElement> m_arrElements;
};

#endif
