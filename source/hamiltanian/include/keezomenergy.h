#ifndef INTERACTION_H
#define INTERACTION_H

#include "potentialenergy.h"

namespace tuco {

struct KeezomEnergy : public ph::PotentialEnergy
{
    KeezomEnergy();
    KeezomEnergy(ph::Energy* energy);
//**Базовые функции и методы:
    void setEnergy(ph::Energy* energy);
    Energy getEnergy();
protected:
    unsigned short numEnergis;
    std::vector<Energy*> energis;
};

}


#endif // INTERACTION_H
