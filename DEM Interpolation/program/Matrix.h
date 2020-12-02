#pragma once
#include <bits/stdc++.h>

class Matrix
{
public:
    double a[25][25];
    int n, m;
    Matrix();
    Matrix(int _n, int _m); // 初始化矩阵
    ~Matrix();
    inline double *operator[](const int &p);
    Matrix operator/(const double &t);                         // 重载矩阵除法
    Matrix operator*(const Matrix &t);                         // 重载矩阵乘法
    Matrix operator*(const double &t);                         // 重载矩阵乘法
    Matrix transpsition();                                     // 求转置矩阵
    Matrix Minor(int _n, int _m);                              // 求余子式
    double value();                                            // 求值
    Matrix adjoint();                                          // 求伴随矩阵
    void One();                                                // 生成单位矩阵
    Matrix inverse();                                          // 矩阵求逆
    void Make_RotM(double varphi, double omega, double kappa); // 建立旋转矩阵
};
// 矩阵类