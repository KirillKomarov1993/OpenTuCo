#include "hamiltanian.h"

namespace tuco {

Hamiltonian::Hamiltonian()
{

}
void Hamiltonian::clear(std::string _key)
{
    if (potentialEnergis.count(_key)) {
        potentialEnergis.erase(_key);
    }
}
void Hamiltonian::setPotentialEnergy(std::string key, ph::PotentialEnergy* potentialEnergy)
{
    if (potentialEnergis.count(key)) {
        potentialEnergis[key]->setEnergy(potentialEnergy);
    } else {
        potentialEnergis[key] = potentialEnergy;
    }
}
ph::Energy* Hamiltonian::getEnergy()
{
    ph::Energy* energy = new ph::Energy();
    for (auto& iEnergy : potentialEnergis) {        
        energy->addEnergy(iEnergy.second->getEnergy().getValue());
    }
    return energy;
}

}
