#ifndef CRYSTALMANAGER_H
#define CRYSTALMANAGER_H

#include "structure.h"
#include "structurebuilder.h"
#include "crystalbuilder.h"
#include "crystal.h"
#include "virtualshift.h"

namespace cs {

class CrystalManager {
    bool flag = false;
    StructureBuilder* structureBuilder;
    CrystalBuilder * crystalBuilder;
protected:
    void constructStructure()
    {
        structureBuilder->createNewStructure();
        structureBuilder->build();
    }
public:
    CrystalManager() :
        structureBuilder(NULL), crystalBuilder(NULL)
    {

    }
    ~CrystalManager()
    {

    }
    void setStructureBuilder(StructureBuilder* builder)
    {
        this->structureBuilder = builder;
    }
    void setCrystalBuilder(CrystalBuilder* builder)
    {
        this->crystalBuilder = builder;
    }
    void constructCrystal()
    {
        constructStructure();
        crystalBuilder->setProperties(structureBuilder->getStructure());
        crystalBuilder->build();
        flag = true;
    }
    std::shared_ptr<Structure> getStructure()
    {
        return structureBuilder->getStructure();
    }
    Crystal* getCrystal()
    {
        return crystalBuilder->getCrystal();
    }
};

}

#endif // CRYSTALMANAGER_H
