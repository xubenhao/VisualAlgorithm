//	Author : XuBenHao      
//	Version : 1.0.0                 
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "matrixtransform.h"
#include "Vector/vector.h"
namespace NTransform
{
    MatrixTransform::MatrixTransform(QObject* parent)
        : Transform(parent)
    {

    }

    MatrixTransform::MatrixTransform(
            const NMatrix::Matrix& mxA_, 
            QObject* parent)
        : Transform(parent)
    {
        m_mxM = mxA_;
    }

    NMatrix::Matrix MatrixTransform::GetMatrix()
    {
        return m_mxM;
    }

    NStruct::Point MatrixTransform::TransPoint(
            const NStruct::Point& poP_)
    {
        NStruct::Point _poRet;
        _poRet.m_nX += m_mxM.m_nData[0][0] * poP_.m_nX;
        _poRet.m_nX += m_mxM.m_nData[0][1] * poP_.m_nY;
        _poRet.m_nX += m_mxM.m_nData[0][2] * 1.0;
        _poRet.m_nY += m_mxM.m_nData[1][0] * poP_.m_nX;
        _poRet.m_nY += m_mxM.m_nData[1][1] * poP_.m_nY;
        _poRet.m_nY += m_mxM.m_nData[1][2] * 1.0;
        return _poRet;
    }

    NStruct::Line MatrixTransform::TransLine(
            const NStruct::Line& nLine_)
    {
        NStruct::Point _poS = TransPoint(nLine_.m_poStart);
        NStruct::Point _poE = TransPoint(nLine_.m_poEnd);
        return NStruct::Line(_poS, _poE);
    }

    NStruct::Rect MatrixTransform::TransRect(
            const NStruct::Rect& nRect_)
    {
        NStruct::Point _poLeftUp = TransPoint(nRect_.m_poLeftUp);
        NStruct::Point _poRightBottom 
            = TransPoint(nRect_.GetRightBottom());
        NStruct::Rect _rcRet;
        _rcRet.m_poLeftUp = _poLeftUp;
        _rcRet.m_nHeight 
            = std::abs(_poLeftUp.m_nY - _poRightBottom.m_nY);
        _rcRet.m_nWeight 
            = std::abs(_poLeftUp.m_nX - _poRightBottom.m_nX);
        NVector::Vector2D _nVec(_poLeftUp, _poRightBottom);
        double _nCalcAngle = _nVec.GetAngle();
        _rcRet.m_nCalcAngle = _nCalcAngle + PI / 4.0;
        return _rcRet;
    }

    NStruct::Ellipse MatrixTransform::TransEllipse(
            const NStruct::Ellipse &nCircle_)
    {
        NStruct::Point _poHLeft;
        NStruct::Point _poHRight;
        NStruct::Point _poVUp;
        NStruct::Point _poVDown;
        _poHLeft.m_nX 
            = nCircle_.m_poCenter.m_nX - nCircle_.m_nHRadius;
        _poHLeft.m_nY 
            = nCircle_.m_poCenter.m_nY;
        _poHRight.m_nX 
            = nCircle_.m_poCenter.m_nX + nCircle_.m_nHRadius;
        _poHRight.m_nY = nCircle_.m_poCenter.m_nY;
        _poVUp.m_nX = nCircle_.m_poCenter.m_nX;
        _poVUp.m_nY 
            = nCircle_.m_poCenter.m_nY - nCircle_.m_nVRadius;
        _poVDown.m_nX = nCircle_.m_poCenter.m_nX;
        _poVDown.m_nY 
            = nCircle_.m_poCenter.m_nY + nCircle_.m_nVRadius;

        NStruct::Point _poNewHLeft = TransPoint(_poHLeft);
        NStruct::Point _poNewHRight = TransPoint(_poHRight);
        NStruct::Point _poNewVUp = TransPoint(_poVUp);
        NStruct::Point _poNewVDown = TransPoint(_poVDown);
        NStruct::Ellipse _nCircle;
        _nCircle.m_poCenter = (_poNewHLeft + _poNewHRight) / 2.0;
        _nCircle.m_nHRadius 
            = Distance(_poNewHLeft, _poNewHRight) / 2.0;
        _nCircle.m_nVRadius 
            = Distance(_poNewVUp, _poNewVDown) / 2.0;
        return _nCircle;
    }

    NStruct::Polyline MatrixTransform::TransPolyline(
            const NStruct::Polyline& nPolyline_)
    {
        NStruct::Polyline _nPoly;
        int _nSize = nPolyline_.m_arrPoints.GetSize();
        for(int i = 0; i < _nSize; i++)
        {
            NStruct::Point _poP 
                = TransPoint(nPolyline_.m_arrPoints[i]);
            _nPoly.m_arrPoints.Add(_poP);
        }
    }

    Transform* MatrixTransform::DeepCopy()
    {
        MatrixTransform* _pTrans = new MatrixTransform();
        _pTrans->m_mxM = m_mxM;
        return _pTrans;
    }

    void MatrixTransform::PrintDebugInfo()
    {
        QString _str;
        _str.sprintf("this is MatrixTransform,");
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                _str += QString().sprintf(
                        "M[%d][%d]=%.2f\n", 
                        i, 
                        j, 
                        m_mxM.m_nData[i][j]);
            }
        }

        QByteArray ba(_str.toUtf8());
        qWarning("%s",ba.data());
    }

    void MatrixTransform::PrintDebugInfo(QFile& hFile_)
    {
        QString _str;
        _str.sprintf("this is MatrixTransform\n");
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                _str += QString().sprintf(
                        "M[%d][%d]=%.2f\n", 
                        i, 
                        j, 
                        m_mxM.m_nData[i][j]);
            }
        }

        QByteArray ba(_str.toUtf8());
        hFile_.write(ba);
        hFile_.flush();
    }
}


// 1.every geometry object support transform to change itself 
// of to get a tranfered geometry
// 2.resource management can according to qt's way.
// parent manager his childs.
// this can form a multi-divide tree
/*Group MatrixTransform::TransGroup(const Group& nGroup_)
{
    int _nSize = nGroup_.m_arrGeometrys.GetSize();
    for(int i = 0; i < _nSize; i++)
    {

    }
}*/


