#include "Matrix.h"

Matrix::Matrix() {}
Matrix::Matrix(int _n, int _m) : n(_n), m(_m)
{
    for (int i = 0; i < _n; i++)
        for (int j = 0; j < _m; j++)
            a[i][j] = 0;
}

Matrix::~Matrix()
{
}

inline double *Matrix::operator[](const int &p)
{
    return a[p];
}

Matrix Matrix::operator/(const double &t)
{
    Matrix temp(n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            temp[i][j] = a[i][j] / t;
    return temp;
}
// 重载矩阵除法

Matrix Matrix::operator*(const Matrix &t)
{
    Matrix temp(n, t.m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < t.m; j++)
            for (int k = 0; k < m; k++)
                temp[i][j] += a[i][k] * t.a[k][j];
    return temp;
}
// 重载矩阵乘法

Matrix Matrix::transpsition()
{
    Matrix temp(m, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            temp[j][i] = a[i][j];
    return temp;
}
// 求转置矩阵

Matrix Matrix::Minor(int _n, int _m)
{
    Matrix temp(n - 1, m - 1);
    for (int i = 0, ti = 0; i < n; i++)
    {
        if (i == _n)
            continue;
        for (int j = 0, tj = 0; j < m; j++)
        {
            if (j == _m)
                continue;
            temp[ti][tj] = a[i][j];
            tj++;
        }
        ti++;
    }
    return temp;
}
// 求余子式

double Matrix::value()
{
    if (n == 1)
        return a[0][0];
    if (n == 2)
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    double ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (i & 1)
            ans -= Minor(i, 0).value() * a[i][0];
        else
            ans += Minor(i, 0).value() * a[i][0];
    }
    return ans;
}
// 求值

Matrix Matrix::adjoint()
{
    Matrix temp(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ((i + j) & 1)
                temp[i][j] = Minor(j, i).value() * -1;
            else
                temp[i][j] = Minor(j, i).value();
        }
    }
    return temp;
}
// 求伴随矩阵

Matrix Matrix::inverse()
{
    Matrix temp(n, m);
    temp = adjoint() / value();
    return temp;
}

void Matrix::One()
{
    for (int i = 0; i < n; i++)
    {
        a[i][i] = 1;
    }
}

void Matrix::Make_RotM(double varphi,double omega,double kappa)
{
    a[0][0] = cos(varphi) * cos(kappa) - sin(varphi) * sin(omega) * sin(kappa);
    a[0][1] = -cos(varphi) * sin(kappa) - sin(varphi) * sin(omega) * cos(kappa);
    a[0][2] = -sin(varphi) * cos(omega);
    a[1][0] = cos(omega) * sin(kappa);
    a[1][1] = cos(omega) * cos(kappa);
    a[1][2] = -sin(omega);
    a[2][0] = sin(varphi) * cos(kappa) + cos(varphi) * sin(omega) * sin(kappa);
    a[2][1] = -sin(varphi) * sin(kappa) + cos(varphi) * sin(omega) * cos(kappa);
    a[2][2] = cos(varphi) * cos(omega);
}

Matrix Matrix::operator*(const double &t){
    Matrix tmp(n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            tmp.a[i][j]=a[i][j]*t;
        }
    }
    return tmp;
}