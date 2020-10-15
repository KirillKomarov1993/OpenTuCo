#ifndef CRYSTALBUILDER_H
#define CRYSTALBUILDER_H

#include "crystal.h"
#include "virtualshift.h"

namespace cs {

// Interface & realization:
class CrystalBuilder
{
protected:
    Crystal* crystal;
public:
    CrystalBuilder();
    virtual ~CrystalBuilder();
    virtual void build() = 0;
    virtual void createNewCrystal() = 0;
    virtual void setProperties(std::shared_ptr<Structure> structure) = 0;
    Crystal* getCrystal();
};

}

#endif // CRYSTALBUILDER_H
