#include "configuration.h"

namespace tuco {

Configurator::Configurator(std::string _name) :
    name_(_name)
{

}
Configurator::~Configurator()
{

}
unsigned long Configurator::getParticleCount()
{
    return numParticles;
}
Vector3d Configurator::getCoordinate(int _nNode)
{
    return coor[_nNode - 1];
}

Pair::Pair(std::string _name) :
    Configurator(_name)
{
    setConfiguration();
}

Triplets::Triplets(std::string _name) :
    Configurator(_name)
{
    setConfiguration();
}

}
