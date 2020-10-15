#include "realcrystalbuilder.h"

namespace cs {

RealCrystalBuilder::RealCrystalBuilder()
{
    createNewCrystal();
}
RealCrystalBuilder::~RealCrystalBuilder()
{

}
void RealCrystalBuilder::createNewCrystal()
{
    crystal = new RealCrystal;
}
void RealCrystalBuilder::setProperties(std::shared_ptr<Structure> structure)
{
    crystal->setStructure(structure);
}
void RealCrystalBuilder::build()
{
    crystal->define(4.0);
}

}
