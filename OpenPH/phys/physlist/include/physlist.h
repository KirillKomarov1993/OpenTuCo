#ifndef PHYSLIST_H
#define PHYSLIST_H

#include <string>
#include "mathlist.h"

namespace ph {
    double epsilon();
    double e();
    double m_e();
    double k_B();
    double E_0();
    double c();
    double k();
//! Functions:
    double getClausiusFactor(double _epsilon);
}
/*
double kg();
double g();

double sm();
double mm();
double um();
double nm();
double keV();

double sec();
double ms();
double us();
double ns();
double ps();
double fs();
double kg();
*/

#endif // PHYSLIST_H
