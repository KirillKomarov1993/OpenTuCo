#include "keezomenergy.h"

namespace tuco {

KeezomEnergy::KeezomEnergy() :
    PotentialEnergy(ph::Energy())
{
    numEnergis = 0;
}
KeezomEnergy::KeezomEnergy(ph::Energy* energy)
{
    this->energy = energy->getValue();
    energis.push_back(energy);
    numEnergis = 1;
}
void KeezomEnergy::setEnergy(ph::Energy* energy)
{
    energis.push_back(energy);
    numEnergis++;
}
ph::Energy KeezomEnergy::getEnergy()
{
    energy = 0.0;
    for (auto& iEnergy : energis) {
        energy += iEnergy->getValue();
    }
    return ph::Energy(energy / numEnergis);
}

}
