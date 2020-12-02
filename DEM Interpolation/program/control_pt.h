#pragma once
#include <bits/stdc++.h>

class control_pt
{
private:

public:
    double index, x, y, z;
    control_pt();
    control_pt(double t[4]);
    ~control_pt();

    double dis(control_pt t); // 求点距
};
// 控制点类