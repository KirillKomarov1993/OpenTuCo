#include "physlist.h"

namespace ph {
    double epsilon()
    {
        return 8.85418781762039e-12;
    }
    double e()
    {
        return 1.6e-19;
    }
    double m_e()
    {
        return 9.10938356e-31;
    }
    double k_B()
    {
        return 1.38e-23;
    }
    double E_0()
    {
        return 511;	//[keV], rest energy for electron
    }
    double c()
    {
        return 3e8;	// [m/sec], speed of light
    }
    double k()
    {
        return 1.0;
        //return 1/(4*math::pi()*epsilon());	// [m/sec], speed of light
    }
    double getClausiusFactor(double _epsilon)
    {
        return (_epsilon - 1.0) / (_epsilon + 2.0);
    }
}
/*
double kg()
{
    return 1.0;
}
double g()
{
    return 1.0e-3;
}


double sm()
{
    return 1e-2;
}
double mm()
{
    return 1e-3;
}
double um()
{
    return 1e-6;
}
double nm()
{
    return 1e-9;
}

double keV()
{
    return 1e-3;
}

double sec()
{
    return 1;
}
double ms()
{
    return 10e-4;
}
double us()
{
    return 10e-7;
}
double ns()
{
    return 10e-10;
}
double ps()
{
    return 10e-13;
}
double fs()
{
    return 10e-16;
}
*/
