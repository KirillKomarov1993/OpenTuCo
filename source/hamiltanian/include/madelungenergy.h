#ifndef BOND_H
#define BOND_H

#include "potentialenergy.h"

namespace tuco {


struct MadelungEnergy : public ph::PotentialEnergy
{
    MadelungEnergy();
    MadelungEnergy(ph::Energy energy);
    ~MadelungEnergy();
    void setEnergy(ph::Energy* energy);
    ph::Energy getEnergy();
protected:
    std::string type;
    std::string name;
};

}

#endif // BOND_H
