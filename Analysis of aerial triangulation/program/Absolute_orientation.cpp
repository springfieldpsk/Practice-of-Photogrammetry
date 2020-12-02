#include "Absolute_orientation.h"

using namespace std;
const double eps = 1e-6;

Absolute_orientation::Absolute_orientation()
{
}

Absolute_orientation::~Absolute_orientation()
{
}

Absolute_orientation::Absolute_orientation(air_belt_network t)
{
    airinf = t.airinf;
    cpt = t.cpt;
}

void Absolute_orientation::cal_trans()
{
    modelpoint t1, ti;
    control_pt p1, pi;
    bool flag = false;
    for (int i = 0; i < (int)airinf.size(); i++)
    {
        for (auto u : airinf[i].mdpts)
        {
            for (auto v : cpt)
            {
                if (u.index != v.index)
                    continue;
                if (!flag)
                {
                    flag = true;
                    t1 = u;
                    p1 = v;
                }
                ti = u;
                pi = v;
                if (!i)
                    cmpt.push_back(Image_control_point(u, v));
            }
        }
    }

    double dXt = p1.x - pi.x;
    double dYt = p1.y - pi.y;
    double dXp = t1.Xm - ti.Xm;
    double dYp = t1.Ym - ti.Ym;

    double tmp = (dXt * dXt + dYt * dYt);
    a = (dYt * dXp + dXt * dYp) / tmp;
    b = (dXt * dXp - dYt * dYp) / tmp;

    lambda = sqrt(a * a + b * b);
    cout << "转换参数 :" << endl;
    cout << "a= " << a << endl;
    cout << "b= " << b << endl;
    cout << "λ= " << lambda << endl;
    cmpt.push_back(Image_control_point(ti, pi));

    // cout<<a<<' '<<b<<' '<<lambda<<endl;
}

void Absolute_orientation::grd2Pgr()
{
    t1 = cmpt[0].cpt;
    for (int i = 0; i < (int)cmpt.size(); i++)
    {
        Image_control_point v = cmpt[i];
        cmpt[i].cpt.x = b * (v.cpt.x - t1.x) + a * (v.cpt.y - t1.y);
        cmpt[i].cpt.y = a * (v.cpt.x - t1.x) - b * (v.cpt.y - t1.y);
        cmpt[i].cpt.z = lambda * (v.cpt.z - t1.z);
    }

    R = Matrix(3, 3);
    L = Matrix(cmpt.size() * 3, 1);
    A = Matrix(cmpt.size() * 3, 7);
}

void Absolute_orientation::trans()
{
    dx += X[0][0];
    dy += X[1][0];
    dz += X[2][0];
    dlamb += X[3][0];
    varphi += X[4][0];
    omega += X[5][0];
    kappa += X[6][0];
}

bool Absolute_orientation::check()
{
    for (int i = 0; i < 7; i++)
        if (abs(X[i][0]) >= eps)
            return false;
    return true;
}

void Absolute_orientation::Barycenterization()
{
    grtc.x = 0, grtc.y = 0, grtc.z = 0;
    grtm.Xm = 0, grtm.Ym = 0, grtm.Zm = 0;

    for (auto v : cmpt)
    {
        grtc.x += v.cpt.x;
        grtc.y += v.cpt.y;
        grtc.z += v.cpt.z;
        grtm.Xm += v.mpt.Xm;
        grtm.Ym += v.mpt.Ym;
        grtm.Zm += v.mpt.Zm;
    }
    grtc.x /= cmpt.size();
    grtc.y /= cmpt.size();
    grtc.z /= cmpt.size();
    grtm.Xm /= cmpt.size();
    grtm.Ym /= cmpt.size();
    grtm.Zm /= cmpt.size();
    for (int i=0;i<(int)cmpt.size();i++)
    {
        cmpt[i].cpt.x -= grtc.x;
        cmpt[i].cpt.y -= grtc.y;
        cmpt[i].cpt.z -= grtc.z;
        cmpt[i].mpt.Xm -= grtm.Xm;
        cmpt[i].mpt.Ym -= grtm.Ym;
        cmpt[i].mpt.Zm -= grtm.Zm;
    }
}

void Absolute_orientation::cal_L()
{
    for (int i = 0; i < (int)cmpt.size(); i++)
    {
        Matrix tmp(3, 1);
        tmp[0][0] = cmpt[i].mpt.Xm;
        tmp[1][0] = cmpt[i].mpt.Ym;
        tmp[2][0] = cmpt[i].mpt.Zm;

        tmp = R * tmp * dlamb;

        L[i * 3][0] = cmpt[i].cpt.x - tmp[0][0] - dx;
        L[i * 3 + 1][0] = cmpt[i].cpt.y - tmp[1][0] - dy;
        L[i * 3 + 2][0] = cmpt[i].cpt.z - tmp[2][0] - dz;
    }
}

void Absolute_orientation::cal_A()
{
    for (int i = 0; i < (int)cmpt.size(); i++)
    {
        A[i * 3][0] = 1;
        A[i * 3][3] = cmpt[i].mpt.Xm;
        A[i * 3][4] = -cmpt[i].mpt.Zm;
        A[i * 3][6] = -cmpt[i].mpt.Ym;

        A[i * 3 + 1][1] = 1;
        A[i * 3 + 1][3] = cmpt[i].mpt.Ym;
        A[i * 3 + 1][5] = -cmpt[i].mpt.Zm;
        A[i * 3 + 1][6] = cmpt[i].mpt.Xm;

        A[i * 3 + 2][2] = 1;
        A[i * 3 + 2][3] = cmpt[i].mpt.Zm;
        A[i * 3 + 2][4] = cmpt[i].mpt.Xm;
        A[i * 3 + 2][5] = cmpt[i].mpt.Ym;
    }
}

void Absolute_orientation::Abs_orienteering()
{
    dx = dy = dz = varphi = kappa = omega = 0;
    dlamb = 1;

    // Barycenterization();

    while (1)
    {
        R.Make_RotM(varphi, omega, kappa);
        // for(int i=0;i<3;i++){
        //     for(int j=0;j<3;j++) cout<<R[i][j]<<' ';
        //     cout<<endl;
        // }
        // cout<<endl;
        cal_L();
        // for(int i=0;i<12;i++){
        //     cout<<L[i][0]<<' ';
        // }
        // cout<<endl<<endl;
        cal_A();

        // for(int i=0;i<12;i++){
        //     for(int j=0;j<7;j++){
        //         cout<<A[i][j]<<' ';
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
        X = (A.transpsition() * A).inverse() * A.transpsition() * L;

        trans();
        if (check())
            break;
        // cout<<dx<<' '<<dy<<' '<<dz<<' '<<dlamb<<' '<<varphi<<' '<<omega<<' '<<kappa<<endl;
    }
    R.Make_RotM(varphi, omega, kappa);

    cout << "绝对定向元素为:" << endl;
    cout << "dx:" << dx << endl;
    cout << "dy:" << dy << endl;
    cout << "dz:" << dz << endl;
    cout << "λ:" << dlamb << endl;
    cout << "φ:" << varphi << endl;
    cout << "ω:" << omega << endl;
    cout << "κ:" << kappa << endl;
}

void Absolute_orientation::air2Pgr()
{
    Matrix tra(3,3);
    tra[0][0]=1;tra[0][1]=-kappa;tra[0][2]=-varphi;
    tra[1][0]=kappa;tra[1][1]=1;tra[1][2]=-omega;
    tra[2][0]=varphi;tra[2][1]=omega;tra[2][2]=1;


    // cout<<varphi<<' '<<omega<<' '<<kappa<<endl;
    for (int j = 0; j < (int)airinf.size(); j++)
    {
        for (int i = 0; i < (int)airinf[j].mdpts.size(); i++)
        {
            modelpoint u = airinf[j].mdpts[i];
            Matrix tmp(3, 1);
            tmp[0][0] = u.Xm;
            tmp[1][0] = u.Ym;
            tmp[2][0] = u.Zm;

            tmp = tra * tmp * dlamb;

            u.Xm = tmp[0][0] + dx;
            u.Ym = tmp[1][0] + dy;
            u.Zm = tmp[2][0] + dz;

            // cout<<u.index<<' '<<u.Xm<<' '<<u.Ym<<' '<<u.Zm<<endl;
            airinf[j].mdpts[i] = u;
        }
        // cout<<endl;
    }
}

void Absolute_orientation::Pgr2grd()
{
    Matrix invt(2, 2);
    invt[0][0] = b;
    invt[0][1] = a;
    invt[1][0] = a;
    invt[1][1] = -b;

    invt  = invt / lambda / lambda;

    for (int j = 0; j < (int)airinf.size(); j++)
    {
        for (int i = 0; i < (int)airinf[j].mdpts.size(); i++)
        {
            modelpoint u = airinf[j].mdpts[i];
            Matrix tmp(2, 1);
            tmp[0][0] = u.Xm;
            tmp[1][0] = u.Ym;

            tmp = invt * tmp;

            airinf[j].mdpts[i].Xm = tmp[0][0] + t1.x;
            airinf[j].mdpts[i].Ym = tmp[1][0] + t1.y;
            airinf[j].mdpts[i].Zm = airinf[j].mdpts[i].Zm / lambda + t1.z;
        }
    }
}
void Absolute_orientation::start()
{
    cal_trans();
    grd2Pgr();
    Abs_orienteering();
    air2Pgr();
    Pgr2grd();
     cout << "最终大地坐标为:" << endl;
    for (auto l : airinf)
    {
        for (auto v : l.mdpts)
        {
            cout << v.index << ' ' << v.Xm << ' ' << v.Ym << ' ' << v.Zm << endl;
        }
    }
    cout << endl;
}
