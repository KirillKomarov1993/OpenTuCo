#include "virtualcrystalbuilder.h"

namespace cs {

VirtualCrystalBuilder::VirtualCrystalBuilder()
{
    createNewCrystal();
}
void VirtualCrystalBuilder::build()
{
    crystal->define(15.0);
}
void VirtualCrystalBuilder::createNewCrystal()
{
    crystal = new VirtualCrystal;
}
void VirtualCrystalBuilder::setProperties(std::shared_ptr<Structure> structure)
{
    crystal->setStructure(structure);
}


}
