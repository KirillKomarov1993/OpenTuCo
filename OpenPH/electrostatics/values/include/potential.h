#ifndef POTENTIAL_H
#define POTENTIAL_H

#include "scalar.h"

namespace ph {

struct ElectricPotential : Scalar
{
    ElectricPotential(Vector3d r);
    ElectricPotential(double scalar, Vector3d r);
    ~ElectricPotential();
protected:
    std::string type;
};


}

#endif // POTENTIAL_H
