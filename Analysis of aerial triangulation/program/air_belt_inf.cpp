#include "air_belt_inf.h"

air_belt_inf::air_belt_inf()
{
}

air_belt_inf::~air_belt_inf()
{
}
air_belt_inf::air_belt_inf(Relative_orientation s,mos _mdpts){
    bx = s.bx;
    by =s.by;
    bz=s.bz;
    mu=s.mu;
    nu=s.nu;
    varphi=s.varphi;
    kappa=s.kappa;
    omega=s.omega;
    mdpts=_mdpts;
    N=s.N;
    Aptp=s.Aptp;
}