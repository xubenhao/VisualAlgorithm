//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef MOVABLEPART_H
#define MOVABLEPART_H
#include "part.h"

namespace NModel
{
    enum MOVE_TYPE
    {
        LINEAR = 1,
        ROTATE,
    };

    class LinearPos
    {
    public:
        LinearPos()
        {
            m_nAngle = 0.0;
            m_nCurPosition = 0.0;
        }

        double m_nAngle;// For Calculate Not For Show
        double m_nCurPosition;
    };

    class RotatePos
    {
    public:
        RotatePos()
        {
            m_nAngle = 0.0;
            m_nRadius = 100.0;
        }

        NStruct::Point m_poCenter;
        double m_nRadius;
        double m_nAngle;
    };

    union ComplexPos
    {
        ComplexPos()
        {

        }

        LinearPos m_nLinearPos;
        RotatePos m_nRotatePos;
    };

    class Position
    {
    public:
        Position()
        {
            m_nMoveType = LINEAR;
            m_nPosition.m_nLinearPos.m_nAngle = 0.0;
            m_nPosition.m_nLinearPos.m_nCurPosition = 0.0;
            m_nPosition.m_nRotatePos.m_nAngle = 0.0;
            m_nPosition.m_nRotatePos.m_poCenter 
                = NStruct::Point(0.0, 0.0);
            m_nPosition.m_nRotatePos.m_nRadius = 100.0;
        }

        NTransform::Transform* GetTransform()
        {
            if(m_nMoveType == LINEAR)
            {
                double _nOffX 
                    = m_nPosition.m_nLinearPos.m_nCurPosition * cos(m_nPosition.m_nLinearPos.m_nAngle / 180.0 * PI);
                double _nOffY 
                    = m_nPosition.m_nLinearPos.m_nCurPosition * sin(m_nPosition.m_nLinearPos.m_nAngle / 180.0 * PI);
                NTransform::LinearTransform* _pTrans 
                    = new NTransform::LinearTransform(_nOffX, _nOffY);
                return _pTrans;
            }
            else if(m_nMoveType == ROTATE)
            {
                NTransform::RotateTransform* _pTrans 
                    = new NTransform::RotateTransform(m_nPosition.m_nRotatePos.m_poCenter, m_nPosition.m_nRotatePos.m_nAngle);
                return _pTrans;
            }
            else
            {
                assert(false);
                return new NTransform::LinearTransform();
            }
        }

        MOVE_TYPE m_nMoveType;
        union ComplexPos m_nPosition;
    };

    union ComplexPosDelta
    {
        ComplexPosDelta()
        {
            m_nAngleDelta = 0.0;
            m_nLengthDelta = 0.0;
        }

        double m_nAngleDelta;
        double m_nLengthDelta;
    };

    class PositionDelta
    {
    public:
        PositionDelta()
        {
            //m_nMoveType = MOVE_TYPE::LINEAR;
        }

        //MOVE_TYPE m_nMoveType;
        //union ComplexPosDelta m_nPosDelta;
        double m_nPosDelta;
    };

    class MovablePart : public Part
    {
    public:
        MovablePart(QObject* parent = nullptr);
        virtual ~MovablePart();

        virtual NTransform::Transform* GetTransform();
        virtual MODEL_TYPE GetType() const{return MODEL_MOVABLEPART;}
        void Delta(double nPosDelta_);
        void SetPosition(Position nPos_){m_nPosition = nPos_;}
        Position GetPosition(){return m_nPosition;}
        virtual void OutputDebugInfo(QFile& hFile_);
    private:
        //NTransform::Transform* m_pCurTransform;
        Position m_nPosition;
    };
}


#endif // MOVABLEPART_H
