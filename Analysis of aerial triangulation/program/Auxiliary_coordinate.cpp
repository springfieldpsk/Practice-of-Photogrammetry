#include "Auxiliary_coordinate.h"

using namespace std;

Auxiliary_coordinate::Auxiliary_coordinate()
{
}

Auxiliary_coordinate::~Auxiliary_coordinate()
{
}

Auxiliary_coordinate::Auxiliary_coordinate(ptopoint t, Matrix R[2], double f)
{
    index = t.index;
    Matrix tmp(3, 1);
    tmp[0][0] = t.x[0];
    tmp[1][0] = t.y[0];
    tmp[2][0] = -f;
    tmp = R[0] * tmp;
    X[0] = tmp[0][0];
    Y[0] = tmp[1][0];
    Z[0] = tmp[2][0];
    tmp[0][0] = t.x[1];
    tmp[1][0] = t.y[1];
    tmp[2][0] = -f;
    tmp = R[1] * tmp;
    X[1] = tmp[0][0];
    Y[1] = tmp[1][0];
    Z[1] = tmp[2][0];
    // 计算像空间辅助坐标
}
