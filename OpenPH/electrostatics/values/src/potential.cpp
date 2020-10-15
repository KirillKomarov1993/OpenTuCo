#include "potential.h"

namespace ph {

ElectricPotential::ElectricPotential(Vector3d r) :
    Scalar(r)
{
    this->scalar  = 0.0;
}
ElectricPotential::ElectricPotential(double scalar, Vector3d r) :
    Scalar(scalar, r)
{

}
ElectricPotential::~ElectricPotential()
{

}

}
