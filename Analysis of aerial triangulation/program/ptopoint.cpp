#include "ptopoint.h"

ptopoint::ptopoint()
{
}

ptopoint::~ptopoint()
{
}

ptopoint::ptopoint(double t[5])
{
    index = t[0];
    x[0] = t[1];
    y[0] = t[2];
    x[1] = t[3];
    y[1] = t[4];
}
