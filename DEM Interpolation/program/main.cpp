#include <bits/stdc++.h>
#include "Matrix.h"
#include "control_pt.h"
#include "readfromfile.h"

using namespace std;

vector<control_pt> ps;

void Make_M(Matrix &M,control_pt p,int i){
    M[i][0]=p.x*p.x;
    M[i][1]=p.x*p.y;
    M[i][2]=p.y*p.y;
    M[i][3]=p.x;
    M[i][4]=p.y;
    M[i][5]=1;
}
int main(int argc, char *args[])
{
    if(argc!=2){
        puts("请通过运行脚本打开程序");
        return -1;
    }
    freopen("ans.out", "w", stdout);
    cout << "开始读入数据......" << endl;
    ps = readfromfile::file2con(args[1]);
    cout << "数据读入完成" << endl;

    double tmp[4]={0,110,110,0};
    control_pt p(tmp);
    Matrix M(ps.size(),6);
    Matrix Z(ps.size(),1);
    Matrix P(ps.size(),ps.size());
    for (int i = 0; i < (int)ps.size(); i++)
    {
        ps[i].x-=p.x;
        ps[i].y-=p.y;
        Make_M(M,ps[i],i);
        Z[i][0]=ps[i].z;
        P[i][i]=1.0/(ps[i].x*ps[i].x+ps[i].y*ps[i].y);
    }
    cout<<"X矩阵为:"<<endl;
    Matrix X = (M.transpsition()*P*M).inverse()*M.transpsition()*P*Z;
    for(int i=0;i<6;i++) cout<<X[i][0]<<endl;
    cout<<endl;

    cout<<"反算结果为:"<<endl;
    Matrix ans = M * X;
    for(int i=0;i<(int)ps.size();i++) {
        cout<<ans[i][0]<<endl;
    }
    cout<<endl;


    cout<<"答案为:"<<endl;
    cout<<X[5][0]<<endl;

}