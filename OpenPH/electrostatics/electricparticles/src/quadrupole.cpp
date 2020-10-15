#include "quadrupole.h"

namespace ph {

Quadrupole::Quadrupole(int _number) :
    ElectricParticle(_number)
{
    type = "quadrupole";
}
Quadrupole::Quadrupole(int _number, Vector3d _r) :
    ElectricParticle(_number, _r), Q(Matrix3d::Zero())
{
    type = "quadrupole";
}
Quadrupole::Quadrupole(int _number, Matrix3d _Q, Vector3d _r) :
    ElectricParticle(_number, _r), Q(_Q)
{
    type = "quadrupole";
}
Quadrupole::~Quadrupole()
{

}
void Quadrupole::clear()
{
    r = Vector3d(0.0, 0.0, 0.0);
    Q = Matrix3d::Zero();
}
ElectricPotential Quadrupole::getElectricPotential(Vector3d _r)
{
    //return ElectricPotential(Q.dot(green->getGradient(_r, r)), _r);
}
ElectricPotential Quadrupole::getElectricPotential(Vector3d _r, GreenKernel* _kernel)
{
    //return ElectricPotential(Q.dot(_kernel->getGradient(_r, r)), _r);
}
ElectricStrength Quadrupole::getElectricStrength(Vector3d _r)
{
    //return ElectricStrength(green->getDipoleOperator(_r, r) * Q);
}
ElectricStrength Quadrupole::getElectricStrength(Vector3d _r, GreenKernel* _kernel)
{
    //return ElectricStrength(_kernel->getDipoleOperator(_r, r) * Q);
}

}
