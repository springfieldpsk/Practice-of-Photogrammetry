#pragma once
#include <bits/stdc++.h>
#include "ptopoint.h"
#include "Matrix.h"

class Auxiliary_coordinate
{
public:
    double index, X[2], Y[2], Z[2], N[2];
    Auxiliary_coordinate();
    Auxiliary_coordinate(ptopoint t, Matrix R[2], double f); // 像空间坐标系转像空间辅助坐标系
    ~Auxiliary_coordinate();
};
// 像空间辅助坐标系类
