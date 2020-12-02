#include "air_belt_network.h"
using namespace std;

air_belt_network::air_belt_network()
{
}

air_belt_network::~air_belt_network()
{
}

air_belt_network::air_belt_network(std::vector<air_belt_inf> _airinf, std::vector<control_pt> _cpt,const double _f)
{
    airinf = _airinf;
    cpt = _cpt;
    f=_f;
}

void air_belt_network::getks()
{
    cout<<"比例尺归化系数为:"<<endl;
    for (int i = 0; i < (int)airinf.size() - 1; i++)
    {
        double k = 0;
        for (auto v : airinf[i].mdpts)
        {
            for (auto u : airinf[i + 1].mdpts)
            {
                if (v.index != u.index)
                    continue;
                k += (v.Zm - airinf[i].bz) / u.Zm;
            }
        }
        ks.push_back(k / 3);
        cout<<k/3<<' ';
    }
    cout<<endl;

}

void air_belt_network::cal_scale()
{
    std::vector<Image_control_point>tmp;
    for (auto u : cpt)
    {
        for (auto v : airinf[0].mdpts)
        {
            if (u.index == v.index)
            {
                tmp.push_back(Image_control_point(v,u));
            }
        }
    } // 寻找像控点

    int tot = 0;
    for (int i = 0; i < (int)tmp.size(); i++)
    {
        for (int j = i + 1; j < (int)tmp.size(); j++)
        {
            tot++;
            m += (tmp[i].cpt.dis(tmp[j].cpt))/(tmp[i].mpt.dis(tmp[j].mpt)) ;
        }
    } //计算实际距离与模型距离之比和
    m /= tot;

    ks.push_back(m);
    cout<<"比例尺为:"<<m<<endl;
}

void air_belt_network::cal_ptos()
{

    for(int i=1;i<(int)ks.size();i++) ks[i]*=ks[i-1]; // 计算归化系数前缀和

    ps.push_back(modelpoint(0,0,m*f));
    for(int i=0;i<(int)airinf.size();i++){
        modelpoint t;
        t.Xm = ps[i].Xm + ks[i]*airinf[i].bx;
        t.Ym = ps[i].Ym + ks[i]*airinf[i].by;
        t.Zm = ps[i].Zm + ks[i]*airinf[i].bz;
        ps.push_back(t);
    }

    // for(auto v:ps){
    //     cout<<v.Xm<<' '<<v.Ym<<' '<<v.Zm<<endl;
    // }
}

void air_belt_network::cal_model()
{
    cal_scale();
    getks();
    cal_ptos();
    for(int i=0;i<(int)airinf.size();i++){
        // cout<<"航带"<<i<<":"<<endl;
        for(int j=0;j<(int)airinf[i].mdpts.size();j++){
            modelpoint u=airinf[i].mdpts[j];
            u.Xm=ps[i].Xm + ks[i] * u.Xm;
            u.Ym=(ps[i].Ym + ks[i] * airinf[i].N[j][0] * airinf[i].Aptp[j].Y[0]+ 
                ps[i+1].Ym + ks[i] * airinf[i].N[j][1] * airinf[i].Aptp[j].Y[1])/2;
            u.Zm=ps[i].Zm + ks[i] * u.Zm;
            airinf[i].mdpts[j]=u;

            // cout<<u.index<<' '<<u.Xm<<' '<<u.Ym<<' '<<u.Zm<<endl;
        }
    }
    // cout<<endl;
}