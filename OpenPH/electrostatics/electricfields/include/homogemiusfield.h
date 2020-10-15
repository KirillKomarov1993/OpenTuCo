#ifndef HOMOGENEOUSFIELD_H
#define HOMOGENEOUSFIELD_H

/*
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
*/

#include "mathlist.h"
#include "strength.h"
#include "scalar.h"
#include "electricfield.h"

namespace ph {

struct HomogeneousField : public ElectricField
{
    HomogeneousField(unsigned long _number, Vector3d _strength);
    Vector3d getDirection();
    ElectricPotential getElectricPotential(Vector3d _r);
    ElectricPotential getElectricPotential(Vector3d _r, Vector3d _r0);
    ElectricStrength getElectricStrength(Vector3d _r);
protected:
    double value;
    Vector3d direction;
};

}

#endif // EHOMOGENEOUSFIELD_H
