#ifndef ELECTRICFILED_H
#define ELECTRICFILED_H

#include "mathlist.h"
#include "electricstrength.h"
#include "potential.h"

namespace ph {

struct ElectricField
{
    ElectricField(unsigned long _number);
    virtual ~ElectricField();
    virtual ElectricPotential getElectricPotential(Vector3d _r) = 0;
    virtual ElectricPotential getElectricPotential(Vector3d _r, Vector3d _r0) = 0;
    virtual ElectricStrength getElectricStrength(Vector3d _r) = 0;
protected:
    unsigned long number;
};


}

#endif // ELECTRICFILED_H
