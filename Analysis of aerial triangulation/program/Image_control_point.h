#pragma once
#include <bits/stdc++.h>
#include "control_pt.h"
#include "modelpoint.h"

class Image_control_point
{
private:
public:
    modelpoint mpt; // 模型点
    control_pt cpt; // 控制点
    Image_control_point();
    Image_control_point(modelpoint a, control_pt b);
    ~Image_control_point();
}; // 像控点类 点号一致的模型点与控制点
