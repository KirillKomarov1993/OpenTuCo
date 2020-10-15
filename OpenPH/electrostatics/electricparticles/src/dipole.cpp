#include "dipole.h"

namespace ph {

Dipole::Dipole(int _number) :
    ElectricParticle(_number)
{
    type = "dipole";
}
Dipole::Dipole(int _number, Vector3d _p) :
    ElectricParticle(_number, Eigen::Vector3d(0.0, 0.0, 0.0)), p(_p)
{
    type = "dipole";
}
Dipole::Dipole(int _number, Vector3d _p, Vector3d _r) :
    ElectricParticle(_number, _r), p(_p)
{
    type = "dipole";
}
Dipole::~Dipole()
{

}
void Dipole::clear()
{
    r = Vector3d(0.0, 0.0, 0.0);
    p = Vector3d(0.0, 0.0, 0.0);
}
ElectricPotential Dipole::getElectricPotential(Vector3d _r)
{
    return ElectricPotential(p.dot(green->getGradient(_r, r)), _r);
}
ElectricPotential Dipole::getElectricPotential(Vector3d _r, GreenKernel* _kernel)
{
    return ElectricPotential(p.dot(_kernel->getGradient(_r, r)), _r);
}
ElectricStrength Dipole::getElectricStrength(Vector3d _r)
{
    return ElectricStrength(green->getDipoleOperator(_r, r) * p);
}
ElectricStrength Dipole::getElectricStrength(Vector3d _r, GreenKernel* _kernel)
{
    return ElectricStrength(_kernel->getDipoleOperator(_r, r) * p);
}

}
