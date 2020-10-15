#ifndef INTERACTIONLIST_H
#define INTERACTIONLIST_H

#include "potentialenergy.h"

namespace tuco {

struct Hamiltonian : public ph::Energy
{
    Hamiltonian();
//**Базовые функции:
    void clear(std::string _key);
    void setPotentialEnergy(std::string key, ph::PotentialEnergy* potentialEnergy);
    ph::Energy* getEnergy();
protected:
    std::map<std::string, ph::PotentialEnergy*> potentialEnergis;
};

}

#endif // INTERACTIONLIST_H
