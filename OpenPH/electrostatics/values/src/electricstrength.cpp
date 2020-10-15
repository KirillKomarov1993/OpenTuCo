#include "electricstrength.h"

namespace ph {

ElectricStrength::ElectricStrength(Vector3d r) :
    Strength(r)
{
    strength = Eigen::Vector3d(0.0, 0.0, 0.0);
}
ElectricStrength::ElectricStrength(Vector3d strength, Vector3d r) :
    Strength(strength, r)
{

}

}
