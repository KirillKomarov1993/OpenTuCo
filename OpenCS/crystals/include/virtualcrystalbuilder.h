#ifndef VIRTUALCRYSTALBUILDER_H
#define VIRTUALCRYSTALBUILDER_H

#include "crystalbuilder.h"
#include "virtualcrystal.h"

namespace cs {

class VirtualCrystalBuilder : public CrystalBuilder
{
    void createNewCrystal();
public:
    VirtualCrystalBuilder();
    void build();    
    void setProperties(std::shared_ptr<Structure> structure);
};

}


#endif // VIRTUALCRYSTALBUILDER_H
