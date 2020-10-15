#include "madelungenergy.h"

namespace tuco {

MadelungEnergy::MadelungEnergy() :
    ph::PotentialEnergy(ph::Energy())
{

}
MadelungEnergy::MadelungEnergy(ph::Energy energy) :
    PotentialEnergy(energy)
{

}
MadelungEnergy::~MadelungEnergy()
{

}
void MadelungEnergy::setEnergy(ph::Energy* energy)
{
    this->energy = energy->getValue();
}
ph::Energy MadelungEnergy::getEnergy()
{
    return energy;
}

}
