#ifndef POTENTIALENERGY_H
#define POTENTIALENERGY_H

#include "energy.h"

namespace ph {

struct PotentialEnergy : public ph::Energy
{
    PotentialEnergy() :
        Energy()
    {

    }
    PotentialEnergy(ph::Energy energy) :
        Energy(energy)
    {

    }
    virtual ~PotentialEnergy()
    {

    }
    virtual void setEnergy(ph::Energy* energy) = 0;
    virtual Energy getEnergy() = 0;
protected:
    std::string type;
    std::string name;
};

}

#endif // POTENTIALENERGY_H
