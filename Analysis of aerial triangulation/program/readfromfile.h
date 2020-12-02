#pragma once
#include <bits/stdc++.h>
#include "ptopoint.h"
#include "control_pt.h"
#include "checkpt.h"

class readfromfile 
{
public:
    static inline FILE *checkfile(const char *filename);           // 文件检测
    static std::vector<ptopoint> file2pto(const char *filename);   // 文件转像对坐标
    static std::vector<control_pt> file2con(const char *filename); // 文件转控制点坐标
    static std::vector<checkpt> file2chk(const char *filename);    // 文件转检查点坐标
};
// 读入文件类