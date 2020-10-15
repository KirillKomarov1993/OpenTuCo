#include "charge.h"


namespace ph {

Charge::Charge(int _number, double _q, Vector3d _r) :
    ElectricParticle(_number, _r), q(_q)
{
    type = "charge";
}
Charge::~Charge()
{

}
void Charge::clear()
{
    r = Vector3d(0.0, 0.0, 0.0);
    q = 0.0;
}
ElectricPotential Charge::getElectricPotential(Vector3d _r)
{
    return ElectricPotential(green->getFunction(_r, r) * q, _r);
}
ElectricStrength Charge::getElectricStrength(Vector3d _r)
{
    return ElectricStrength(-green->getGradient(_r, r) * q, _r);
}

}
