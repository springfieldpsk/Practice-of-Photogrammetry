#pragma once

#include <bits/stdc++.h>
#include "modelpoint.h"
#include "control_pt.h"
#include "air_belt_inf.h"
#include "Image_control_point.h"

typedef std::vector<modelpoint> mos;

class air_belt_network
{
private:
    std::vector<double> ks;     // 模型比例尺规划系数
    std::vector<modelpoint> ps; // 各模型摄站摄影测量坐标
    double m;                   // 比例尺
    double f;

public:
    std::vector<control_pt> cpt;      // 控制点坐标
    std::vector<air_belt_inf> airinf; // 航带信息
    air_belt_network();
    air_belt_network(std::vector<air_belt_inf> _airinf, std::vector<control_pt> cpt, const double _f);
    ~air_belt_network();

    void getks();     // 生成比例尺规划系数
    void cal_scale(); // 计算比例尺
    void cal_ptos();  // 计算各模型摄站摄影测量坐标
    void cal_model(); // 计算最终模型点坐标
};
// 航带网类
