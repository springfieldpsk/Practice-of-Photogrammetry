#pragma once
#include <bits/stdc++.h>

class modelpoint
{

public:
    double index,Xm,Ym,Zm;
    modelpoint();
    modelpoint(double _x,double _y,double _z);
    ~modelpoint();

    double dis(modelpoint t); // 求点距 
};
// 模型点坐标类


