#include "Relative_orientation.h"

const double eps = 3e-5;
using namespace std;

Relative_orientation::Relative_orientation()
{
}

Relative_orientation::~Relative_orientation()
{
}

Relative_orientation::Relative_orientation(std::vector<ptopoint> t, Matrix Rt,double _bx, double _f)
{
    ptp = t;
    bx = _bx;
    by = bz = mu = nu = 0;
    varphi = kappa = omega = 0;
    f = _f;
    R[0] = Rt;
    R[1] = Matrix(3, 3);
    A = Matrix(t.size(), 5);
    L = Matrix(t.size(), 1);
    N = Matrix(t.size(), 2);

}

bool Relative_orientation::check()
{
    for (int i = 0; i < 5; i++)
        if (abs(X[i][0]) >= eps)
            return false;
    return true;
}

void Relative_orientation::tran()
{
    mu += X[0][0];
    nu += X[1][0];
    varphi += X[2][0];
    omega += X[3][0];
    kappa += X[4][0];
    by = bx * mu;
    bz = bx * nu;
}

void Relative_orientation::Make_Aux()
{
    Aptp.clear();
    for (int i = 0; i < (int)ptp.size(); i++)
    {
        Aptp.push_back(Auxiliary_coordinate(ptp[i], R, f));

        Auxiliary_coordinate now = *(Aptp.end() - 1);
        double temp = now.X[0] * now.Z[1] - now.X[1] * now.Z[0];
        N[i][0] = (bx * now.Z[1] - bz * now.X[1]) / temp;
        N[i][1] = (bx * now.Z[0] - bz * now.X[0]) / temp;
        // 计算投影系数
        // cout<<now.index<<endl;
        // cout<<now.X[0]<<' '<<now.Y[0]<<' '<<now.Z[0]<<endl;
        // cout<<now.X[1]<<' '<<now.Y[1]<<' '<<now.Z[1]<<endl;
        // cout<<N[i][0]<<' '<<N[i][1]<<endl;

        A[i][0] = bx;
        A[i][1] = -(now.Y[1] * bx) / now.Z[1];
        A[i][2] = -(now.X[1] * now.Y[1]) * N[i][1] / now.Z[1];
        A[i][3] = -(now.Z[1] + now.Y[1] * now.Y[1] / now.Z[1]) * N[i][1];
        A[i][4] = now.X[1] * N[i][1];
        // 计算A矩阵
        L[i][0] = N[i][0] * now.Y[0] - N[i][1] * now.Y[1] - by;
        // 计算L矩阵

        // for(int j=0;j<5;j++) cout<<A[i][j]<<' ';
        // cout<<endl;
        // cout<<L[i][0]<<endl;
    }
}

void Relative_orientation::Solve_Ro()
{
    int cnt = 0;
    // cout<<bx<<' '<<by<<' '<<bz<<' '<<mu<<' '<<varphi<<' '<<kappa<<' '<<omega<<endl;
    while (1)
    {
        cnt++;
        // cout<<cnt<<endl;
        R[1].Make_RotM(varphi,omega,kappa);
        // for(int i=0;i<3;i++){
        //     for(int j=0;j<3;j++){
        //         cout<<R[1][i][j]<<' ';
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
        Make_Aux();
        // cout<<endl;
        X = (A.transpsition() * A).inverse() * A.transpsition() * L;
        // cout<<endl;
        // cout<<X.n<<' '<<X.m<<endl;
        // for(int i=0;i<X.n;i++){
        //     for(int j=0;j<X.m;j++){
        //         cout<<X[i][j]<<' ';
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
        // cout<<by<<' '<<bz<<' '<<mu<<' '<<nu<<' '<<varphi<<' '<<omega<<' '<<kappa<<endl;
        if (check()){
            varphi += X[2][0];
            omega += X[3][0];
            kappa += X[4][0];
            break;
        }
        tran();
    }
    R[1].Make_RotM(varphi,omega,kappa);

    cout << "迭代完成 共进行" << cnt << "次迭代" << endl;
    cout << "bx=" << bx << "  by=" << by << "  bz=" << bz << endl;
    cout<<"μ="<<mu<<' '<<"  v="<<nu<<endl;
    cout << "φ=" << varphi << "  ω=" << omega << "  κ=" << kappa << endl;

    // cout<<"N="<<endl;
    // for(int i=0;i<(int)ptp.size();i++) cout<<N[i][0]<<' '<<N[i][1]<<endl;
    // cout<<endl;
}

std::vector<modelpoint> Relative_orientation::Make_modelpoint(){
    vector<modelpoint>t;
    for(int i=0;i<Aptp.size();i++){
        modelpoint tmp;
        tmp.index=Aptp[i].index;
        tmp.Xm=N[i][0]*Aptp[i].X[0];
        tmp.Ym=(N[i][0]*Aptp[i].Y[0]+N[i][1]*Aptp[i].Y[1]+by)/2;
        tmp.Zm=N[i][0]*Aptp[i].Z[0];
        t.push_back(tmp);
    }
    return t;
}