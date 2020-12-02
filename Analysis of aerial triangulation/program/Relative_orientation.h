#pragma once
#include <bits/stdc++.h>
#include "Matrix.h"
#include "ptopoint.h"
#include "Auxiliary_coordinate.h"
#include "modelpoint.h"

class Relative_orientation
{
private:
    Matrix A, L, X;
    std::vector<ptopoint> ptp; // 像平面点
    double Q, f;

public:
    std::vector<Auxiliary_coordinate> Aptp; // 像空间辅助坐标点
    Matrix R[2], N;
    double bx, by, bz, mu, nu, varphi, kappa, omega; // 相对定向元素
    Relative_orientation();
    Relative_orientation(std::vector<ptopoint> t, Matrix Rt, double _bx, double _f);
    ~Relative_orientation();

    void Solve_Ro();                           // 开始进行相对定位运算
    bool check();                              // 检查
    void tran();                               // 改正相对方位元素
    void Make_Aux();                           // 生成像空间辅助坐标系坐标
    std::vector<modelpoint> Make_modelpoint(); // 计算模型点坐标
};
