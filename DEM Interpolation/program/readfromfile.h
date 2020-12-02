#pragma once
#include <bits/stdc++.h>
#include "control_pt.h"


class readfromfile 
{
public:
    static inline FILE *checkfile(const char *filename);           // 文件检测
    static std::vector<control_pt> file2con(const char *filename); // 文件转控制点坐标
};
// 读入文件类