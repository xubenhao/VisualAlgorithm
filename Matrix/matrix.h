//	Author : XuBenHao
//	Version : 1.0.0
//	Mail : xbh370970843@163.com
//	Copyright : XuBenHao 2020 - 2030

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include "header.h"

namespace NTransform
{
    class MatrixTransform;
}

namespace NMatrix
{
    class Matrix
    {
    public:
        explicit Matrix();
        explicit Matrix(double (&nRow0_)[3][3]);

        void Offset(double nOffX_, double nOffY_);
        void Rotate(double nAngle_);
        void Scale(double nScaleX_, double nScaleY_);

        Matrix operator*(const Matrix& mxA_);
        Matrix Invert();
        Matrix GetOffset(double nOffX_, double nOffY_);
        Matrix GetRotate(double nAngle_);
        Matrix GetScale(double nScaleX_, double nScaleY_);
        double GetValue();
        double GetMxx(int nIndex1_, int nIndex2_);
        double GetAxx(int nIndex1_, int nIndex2_);

        friend class NTransform::MatrixTransform;
    private:
        double m_nData[3][3];
    };
}

#endif // MATRIX_H
