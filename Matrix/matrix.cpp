//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#include "matrix.h"

namespace NMatrix
{
    Matrix::Matrix()
    {
        memset(m_nData, 0, sizeof(m_nData));
        m_nData[0][0] = 1.0;
        m_nData[1][1] = 1.0;
        m_nData[2][2] = 1.0;
    }

    Matrix::Matrix(double (&nRow0_)[3][3])
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                m_nData[i][j] = nRow0_[i][j];
            }
        }
    }

    void Matrix::Offset(double nOffX_, double nOffY_)
    {
        Matrix _mxA;
        _mxA.m_nData[0][2] = nOffX_;
        _mxA.m_nData[1][2] = nOffY_;
        _mxA.operator*(*this);
        *this = _mxA;
    }

    void Matrix::Rotate(double nAngle_)
    {
        nAngle_ = (nAngle_ / 180.0) * PI;
        Matrix _mxA;
        _mxA.m_nData[0][0] = cos(nAngle_);
        _mxA.m_nData[0][1] = -sin(nAngle_);
        _mxA.m_nData[1][0] = sin(nAngle_);
        _mxA.m_nData[1][1] = cos(nAngle_);
        _mxA.operator*(*this);
        *this = _mxA;
    }

    void Matrix::Scale(double nScaleX_, double nScaleY_)
    {
        Matrix _mxA;
        _mxA.m_nData[0][0] = nScaleX_;
        _mxA.m_nData[1][1] = nScaleY_;
        _mxA.operator*(*this);
        *this = _mxA;
    }


    Matrix Matrix::GetOffset(double nOffX_, double nOffY_)
    {
        Matrix _mxA;
        _mxA.m_nData[0][2] = nOffX_;
        _mxA.m_nData[1][2] = nOffY_;
        _mxA.operator*(*this);
        return _mxA;
    }

    Matrix Matrix::GetRotate(double nAngle_)
    {
        Matrix _mxA;
        _mxA.m_nData[0][0] = cos(nAngle_);
        _mxA.m_nData[0][1] = -sin(nAngle_);
        _mxA.m_nData[1][0] = sin(nAngle_);
        _mxA.m_nData[1][1] = cos(nAngle_);
        _mxA.operator*(*this);
        return _mxA;
    }

    Matrix Matrix::GetScale(double nScaleX_, double nScaleY_)
    {
        Matrix _mxA;
        _mxA.m_nData[0][0] = nScaleX_;
        _mxA.m_nData[1][1] = nScaleY_;
        _mxA.operator*(*this);
        return _mxA;
    }

    Matrix Matrix::operator*(const Matrix& mxA_)
    {
        Matrix _mxRet;
        memset(_mxRet.m_nData, 0, sizeof(_mxRet.m_nData));
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    _mxRet.m_nData[i][j] 
                        += this->m_nData[i][k] * mxA_.m_nData[k][j];
                }
            }
        }

        return _mxRet;
    }


    Matrix Matrix::Invert()
    {
        Matrix _mxRet;
        double _nValue = GetValue();
        if(abs(_nValue) <= 0.000001)
        {
            throw "Invert Error";
        }

        //double _nInvert[3][3];
        double _nV = 1.0 / _nValue;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                _mxRet.m_nData[i][j] = _nV * GetAxx(j, i);
            }
        }

        return _mxRet;
    }

    double Matrix::GetValue()
    {
        double _nValue = 0.0;
        _nValue += m_nData[0][0] * m_nData[1][1] * m_nData[2][2];
        _nValue += m_nData[0][1] * m_nData[1][2] * m_nData[2][0];
        _nValue += m_nData[0][2] * m_nData[1][0] * m_nData[2][1];

        _nValue -= m_nData[0][0] * m_nData[1][2] * m_nData[2][1];
        _nValue -= m_nData[1][0] * m_nData[0][1] * m_nData[2][2];
        _nValue -= m_nData[0][2] * m_nData[2][0] * m_nData[1][1];
        return _nValue;
    }

    double Matrix::GetMxx(int nIndex1_, int nIndex2_)
    {
        if(nIndex1_ < 0 || nIndex1_ > 2)
        {
            throw "Index Error";
        }

        if(nIndex2_ < 0 || nIndex2_ > 2)
        {
            throw "Index Error";
        }

        double _nMxx[2][2];
        for(int i = 0; i < 3; i++)
        {
            if(i == nIndex1_)
            {
                continue;
            }

            for(int j = 0; j < 3; j++)
            {
                if(j == nIndex2_)
                {
                    continue;
                }

                _nMxx[i][j] = m_nData[i][j];
            }
        }


        return (_nMxx[0][0]*_nMxx[1][1] - _nMxx[0][1]*_nMxx[1][0]);
    }

    double Matrix::GetAxx(int nIndex1_, int nIndex2_)
    {
        double _nMxx = GetMxx(nIndex1_, nIndex2_);
        return (nIndex1_ + nIndex2_) / 2 ? (-1*_nMxx) : _nMxx;
    }
}

