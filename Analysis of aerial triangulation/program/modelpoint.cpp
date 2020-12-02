#include "modelpoint.h"

modelpoint::modelpoint()
{
}
modelpoint::modelpoint(double _x,double _y,double _z){
    Xm=_x;
    Ym=_y;
    Zm=_z;
}
modelpoint::~modelpoint()
{
}

double modelpoint::dis(modelpoint t){
    return sqrt((Xm-t.Xm)*(Xm-t.Xm)+(Ym-t.Ym)*(Ym-t.Ym));
}