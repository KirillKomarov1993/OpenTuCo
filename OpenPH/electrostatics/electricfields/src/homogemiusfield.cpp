#include "homogemiusfield.h"

namespace ph {

HomogeneousField::HomogeneousField(unsigned long _number, Vector3d strength) :
    ElectricField(_number), value(strength.norm())
{
    this->direction = strength / value;
}
Vector3d HomogeneousField::getDirection()
{
    return direction;
}
ElectricPotential HomogeneousField::getElectricPotential(Vector3d _r)
{
    return ElectricPotential(-value * direction.dot(_r), _r);
}
ElectricPotential HomogeneousField::getElectricPotential(Vector3d _r, Vector3d _r0)
{
    return ElectricPotential(-value * direction.dot(_r - _r0), _r);
}
ElectricStrength HomogeneousField::getElectricStrength(Vector3d _r)
{
    return ElectricStrength(value * direction, _r);
}

}
