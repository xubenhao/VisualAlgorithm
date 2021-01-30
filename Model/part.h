//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef MODEL_PART_H
#define MODEL_PART_H
#include "header.h"

namespace NModel
{
    class Part : public QObject
    {
        Q_OBJECT
    public:
        Part(QObject* parent = nullptr);
        virtual ~Part();
        virtual void Draw(QImage* pImage_);

        virtual NTransform::Transform* GetTransform();
        virtual void OutputDebugInfo(QFile& hFile_);
        Part* GetParent();

        virtual void SetInitialTransform(
                NTransform::Transform* pTrans_)
        {
            m_pInitialTransform = pTrans_;
        }
        
        virtual NTransform::Transform* GetInitialTransform()
        {
            return m_pInitialTransform;
        }
        
        void SetDrawing(NDrawing::Drawing* pDrawing_)
        {
            m_pDrawing = pDrawing_;
        }
        
        NDrawing::Drawing* GetDrawing()
        {
            return m_pDrawing;
        }
        
        void SetParent(Part* pParent_)
        {
            m_pParent = pParent_;
        }
        
        virtual void AddChild(Part* pChild_)
        {
            m_arrChilds.Add(pChild_);
        }
        
        virtual void RemoveChild(Part* pChild_)
        {
            m_arrChilds.DeleteByValue(pChild_);
        }
        
        virtual MODEL_TYPE GetType() const{return MODEL_PART;}

        char* GetName(){return m_strName;}
        void SetName(char (&strName_)[100]);
        void SetName(const QByteArray& nByteArr_);
        void SetObjectId(long nObjectId_){m_nObjectID = nObjectId_;}
        long GetObjectId(){return m_nObjectID;}
    protected:
        // Initial Layout
        NTransform::Transform* m_pInitialTransform;

        NDrawing::Drawing* m_pDrawing;

        // Relation
        Part* m_pParent;
        NDataStruct::DynArray<Part*> m_arrChilds;
        char m_strName[100];
        long m_nObjectID;
    };
}


#endif // PART_H

