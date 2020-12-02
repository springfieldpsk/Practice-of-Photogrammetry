#pragma GCC optimize(3, "Ofast", "inline")

#if _MSC_VER
#include <cmath>
#include <cstdio>
#include <vector>

#else

#include <bits/stdc++.h>

#endif

#include "Matrix.h"
#include "ptopoint.h"
#include "control_pt.h"
#include "checkpt.h"
#include "readfromfile.h"
#include "Auxiliary_coordinate.h"
#include "Relative_orientation.h"
#include "modelpoint.h"
#include "air_belt_inf.h"
#include "air_belt_network.h"
#include "Absolute_orientation.h"
#include "Image_control_point.h"

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const double eps = 3e-5;
const double f = 153.033 / 1000;
const double bx = 200.0 / 1000;
typedef std::vector<modelpoint> mos;

vector<ptopoint> img_pair[3];
Relative_orientation g[3];
vector<control_pt> con;
vector<checkpt> chk;
vector<air_belt_inf> air_b;
air_belt_network air_n;
Absolute_orientation Abs_o;

int main(int argc, char *args[])
{
    if(argc!=6){
        puts("请通过运行脚本打开程序");
        return -1;
    }
    freopen("ans.out", "w", stdout);
    cout << "开始读入数据......" << endl;
    img_pair[0] = readfromfile::file2pto(args[1]);
    img_pair[1] = readfromfile::file2pto(args[2]);
    img_pair[2] = readfromfile::file2pto(args[3]);
    con = readfromfile::file2con(args[4]);
    chk = readfromfile::file2chk(args[5]);
    cout << "数据读入完成" << endl;

    cout << "开始相对定向......" << endl;
    Matrix R = Matrix(3, 3);
    R.One();
    for (int i = 0; i < 3; i++)
    {
        mos m;
        g[i] = Relative_orientation(img_pair[i], R, bx, f);
        g[i].Solve_Ro();
        m = g[i].Make_modelpoint();
        air_b.push_back(air_belt_inf(g[i], m));
        R = g[i].R[1];
    }
    cout << "相对定向完成" << endl;

    cout << "开始建立航带网模型......" << endl;
    air_n = air_belt_network(air_b, con, f);
    air_n.cal_model();
    cout << "航带网模型建立完成" << endl;

    cout << "开始模型的绝对定向......" << endl;
    Abs_o = Absolute_orientation(Absolute_orientation(air_n));
    Abs_o.start();
    cout << "模型的绝对定向完成" << endl;

    cout << "差值为:" << endl;
    for (auto u : chk)
    {
        bool flag = false;
        for (auto l : Abs_o.airinf)
        {
            for (auto v : l.mdpts)
            {
                if (v.index != u.index)
                    continue;
                cout << v.index << ' ' << u.x - v.Xm << ' ' << u.y - v.Ym << ' ' << u.z - v.Zm << endl;
                flag = true;
                break;
            }
            if (flag)
                break;
        }
    }

    return 0;
}