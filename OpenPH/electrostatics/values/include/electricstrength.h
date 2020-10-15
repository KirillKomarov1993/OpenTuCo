#ifndef ELECTRICSTRENGTH_H
#define ELECTRICSTRENGTH_H

#include "strength.h"

namespace ph {

struct ElectricStrength : Strength
{
    ElectricStrength(Vector3d r);
    ElectricStrength(Vector3d strength, Vector3d r);
protected:
    std::string type;
};

}

#endif // ELECTRICSTRENGTH_H
