//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "movablepart.h"

namespace NModel
{
    MovablePart::MovablePart(QObject* parent)
        : Part(parent),m_nPosition()
    {
        //m_pCurTransform = nullptr;
    }

    MovablePart::~MovablePart()
    {

    }


    NTransform::Transform* MovablePart::GetTransform()
    {
        // 1.get accumulate transform from all parent
        NTransform::TransformGroup* _pTransGroup = new NTransform::TransformGroup();
        if(m_pInitialTransform)
        {
            _pTransGroup->Add(m_pInitialTransform);
        }

        //if(m_pCurTransform)
        //{
        //    _pTransGroup->Add(m_pCurTransform);
        //}
        _pTransGroup->Add(m_nPosition.GetTransform());
        return _pTransGroup;
    }

    void MovablePart::Delta(double nPosDelta_)
    {
        if(m_nPosition.m_nMoveType == MOVE_TYPE::LINEAR)
        {
            m_nPosition.m_nPosition.m_nLinearPos.m_nCurPosition += nPosDelta_;
        }
        else if(m_nPosition.m_nMoveType == MOVE_TYPE::ROTATE)
        {
            m_nPosition.m_nPosition.m_nRotatePos.m_nAngle += nPosDelta_;
        }
        else
        {
            assert(false);
            return;
        }
    }

    void MovablePart::OutputDebugInfo(QFile& hFile_)
    {
        QString _str = QString::asprintf(
                    "MovePart's DebugInfo\n");
        QByteArray _nByteArr = _str.toUtf8();
        hFile_.write(_nByteArr);
        hFile_.flush();

        if(m_nPosition.m_nMoveType == MOVE_TYPE::LINEAR)
        {
            _str = QString::asprintf(
                        "MoveType:Linear\n");
            _nByteArr = _str.toUtf8();
            hFile_.write(_nByteArr);
            hFile_.flush();
            _str = QString::asprintf(
                        "Position:Angle=%.3f,Position=%.3f\n",
                        m_nPosition.m_nPosition.m_nLinearPos.m_nAngle,
                        m_nPosition.m_nPosition.m_nLinearPos.m_nCurPosition);
            _nByteArr = _str.toUtf8();
            hFile_.write(_nByteArr);
            hFile_.flush();
        }
        else if(m_nPosition.m_nMoveType == MOVE_TYPE::ROTATE)
        {
            _str = QString::asprintf(
                        "MoveType:Rotate\n");
            _nByteArr = _str.toUtf8();
            hFile_.write(_nByteArr);
            hFile_.flush();
            _str = QString::asprintf(
                        "Position:Center.X=%.3f,CenterY=%.3f,Radius=%.3f,Angle=%.3f\n",
                        m_nPosition.m_nPosition.m_nRotatePos.m_poCenter.GetX(),
                        m_nPosition.m_nPosition.m_nRotatePos.m_poCenter.GetY(),
                        m_nPosition.m_nPosition.m_nRotatePos.m_nRadius,
                        m_nPosition.m_nPosition.m_nRotatePos.m_nAngle);
            _nByteArr = _str.toUtf8();
            hFile_.write(_nByteArr);
            hFile_.flush();
        }
        else
        {
            assert(false);
            return;
        }

        Part::OutputDebugInfo(hFile_);
    }
}

