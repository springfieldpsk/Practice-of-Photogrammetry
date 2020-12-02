#include "control_pt.h"

control_pt::control_pt()
{
}

control_pt::~control_pt()
{
}

control_pt::control_pt(double t[4])
{
    index = t[0];
    x = t[1];
    y = t[2];
    z = t[3];
}

double control_pt::dis(control_pt t){
    return sqrt((x-t.x)*(x-t.x)+(y-t.y)*(y-t.y));
}