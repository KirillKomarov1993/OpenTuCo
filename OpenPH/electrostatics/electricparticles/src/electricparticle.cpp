#include "electricparticle.h"

namespace ph {

ElectricParticle::ElectricParticle(int _number) :
    number(_number)
{
    green = new CoulombKernal();
    type = "electro";
}
ElectricParticle::ElectricParticle(int _number, Vector3d _r) :
    number(_number), r(_r)
{
    green = new CoulombKernal();
    type = "electro";
}
ElectricParticle::~ElectricParticle()
{

}
void ElectricParticle::setPosition(Vector3d r)
{
    this->r = r;
}
Vector3d ElectricParticle::getPosition()
{
    return r;
}
std::string ElectricParticle::getType()
{
    return type;
}

}
