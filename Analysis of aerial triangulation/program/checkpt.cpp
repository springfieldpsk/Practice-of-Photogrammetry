#include "checkpt.h"

checkpt::checkpt()
{
}

checkpt::checkpt(double t[4])
{
    index = t[0];
    x = t[1];
    y = t[2];
    z = t[3];
}

checkpt::~checkpt()
{
}
