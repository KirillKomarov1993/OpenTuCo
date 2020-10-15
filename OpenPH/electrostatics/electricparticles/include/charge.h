#ifndef CHARGE_H
#define CHARGE_H

#include "electricparticle.h"
#include "potential.h"
#include "electricstrength.h"

namespace ph {

struct Charge : ElectricParticle
{
    Charge(int _number, double _q, Vector3d _r);
    ~Charge();
    void clear();
    ElectricPotential getElectricPotential(Vector3d _r);
    ElectricStrength getElectricStrength(Vector3d _r);
protected:
    double q;
};

}

#endif // CHARGE_H
