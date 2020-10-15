#include "particle.h"

namespace cs {

Particle::~Particle()
{
}
void Particle::setEnergy(ph::Energy energy)
{
    this->energy_ = energy;
}
ph::Energy Particle::getEnergy()
{
    return energy_;
}
unsigned long Particle::getNumber()
{
    return number_;
}

}

