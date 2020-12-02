#pragma once
#include <bits/stdc++.h>
#include "air_belt_network.h"
#include "Matrix.h"

typedef std::vector<modelpoint> mos;
typedef std::vector<Image_control_point> IMCPT;

class Absolute_orientation
{
private:
    double lambda, a, b;    // 转换参数 a,b,λ
    std::vector<control_pt> cpt; // 控制点坐标
    IMCPT cmpt;                  // 像控点坐标
    double dx, dy, dz, dlamb, varphi, kappa, omega;
    Matrix R, A, L, X;
    control_pt grtc; // 控制点重心坐标
    modelpoint grtm; // 模型点重心坐标
    control_pt t1;
public:
    std::vector<air_belt_inf> airinf; // 航带信息
    Absolute_orientation();
    Absolute_orientation(air_belt_network t);
    ~Absolute_orientation();

    void cal_trans();         // 计算转换参数 a,b,λ
    void grd2Pgr();           // 由地面坐标转摄影测量坐标
    void Abs_orienteering();  // 绝对定向
    void air2Pgr();           // 由航带坐标转地面摄测坐标
    void Pgr2grd();           // 由地面摄测坐标转大地坐标
    void cal_L();             // 计算L矩阵
    void cal_A();             // 计算A矩阵
    void Barycenterization(); // 重心化坐标
    bool check();             // 检查
    void trans();             // 改正误差
    void start();             // 开始定向
};
