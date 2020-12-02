#pragma once

#include <bits/stdc++.h>
#include "modelpoint.h"
#include "Relative_orientation.h"

typedef std::vector<modelpoint> mos;

class air_belt_inf
{

public:
    mos mdpts;                              // 模型点
    std::vector<Auxiliary_coordinate> Aptp; // 像空间辅助坐标点
    Matrix N;
    double bx, by, bz, mu, nu, varphi, kappa, omega;
    air_belt_inf();
    air_belt_inf(Relative_orientation s, mos _mdpts);
    ~air_belt_inf();
}; // 航道信息类
