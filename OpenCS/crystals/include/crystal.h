#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "mathlist.h"
#include "physlist.h"
#include "unitcell.h"
#include "structure.h"
#include "energy.h"
#include "elasticproperties.h"
#include "virtualshift.h"
#include "brillouinzone.h"

#include <map>

namespace cs {

//!*Здесь реализован паттерн "Наблюдатель" для объекта <<Crystal>>:

struct ElasticModulus
{
    ElasticModulus()
    {

    }
    void setModule(unsigned short _key, Vector3d _module)
    {
        modules[_key] = _module;
    }
    Vector3d getModule(unsigned short _key)
    {
        return modules[_key];
    }
protected:
    int indice;
    std::map<unsigned short, Vector3d> modules;
};

struct Crystal
{
    Crystal();
    virtual ~Crystal();
    void setBrillouinZone()
    {
        structure->setBrillouinZone();
    }
    unsigned long getDimension()
    {
        return getStructure()->getMainLattice()->getBravaisLattice()->getBasis()->getDimension();
    }
    unsigned long getCountCells();
    bool isMainUnitCell(Node* node);
    bool isMainUnitCell(UnitCell* unitCell);
    std::shared_ptr<Structure> getStructure();
    std::shared_ptr<UnitCell> getMainUnitCell();
    std::vector<UnitCell*> getUnitCells();
    ElasticModulus* getElasticModulus()
    {
        return elasticModulus;
    }
    BrillouinZone* getBrillouinZone()
    {
        return structure->getBrillouinZone();
    }
    virtual void record(std::string _address, std::string _name) = 0;
    virtual void setStructure(std::shared_ptr<Structure> structure) = 0;
    virtual void define(double) = 0;
    virtual void setVariation(VirtualShift* _shift) = 0;
    virtual void removeVariation() = 0;    
    virtual ph::Energy getUnitCellEnergy()
    {
        ph::Energy energy;
        for (auto iNode : *getMainUnitCell()->getNodes()) {
            energy += iNode->getParticle()->getEnergy();
        }
        return energy;
    }
protected:
    unsigned long numCells;
    std::shared_ptr<Structure> structure;
    ElasticModulus* elasticModulus;
    std::shared_ptr<UnitCell> mainUnitCell;
    std::vector<UnitCell*> cells;

//! List of the observers:
};


}


#endif // CRYSTAL_H
