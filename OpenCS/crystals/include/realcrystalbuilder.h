#ifndef REALCRYSTALBUILDER_H
#define REALCRYSTALBUILDER_H

#include "crystalbuilder.h"
#include "realcrystal.h"

namespace cs {

class RealCrystalBuilder : public CrystalBuilder
{
    void createNewCrystal();
public:
    RealCrystalBuilder();
    ~RealCrystalBuilder();
    void setProperties(std::shared_ptr<Structure> structure);
    void build();
};

}

#endif // REALCRYSTALBUILDER_H
