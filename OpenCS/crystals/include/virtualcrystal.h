#ifndef VIRTUALCRYSTAL_H
#define VIRTUALCRYSTAL_H

#include "mathlist.h"
#include "physlist.h"
#include "unitcell.h"
#include "structure.h"
#include "energy.h"
#include "virtualshift.h"
#include "crystal.h"
#include "virtualnode.h"

namespace cs {

struct VirtualCrystal : public Crystal
{
    VirtualCrystal();
    VirtualCrystal(Crystal* crystal) :
        Crystal(*crystal)
    {

    }
    ~VirtualCrystal();
    void setStructure(std::shared_ptr<Structure> structure);
    void define(double);
    void record(std::string _address, std::string _name);
    void setVariation(VirtualShift* _shift);
    void removeVariation();
};

}



#endif // VIRTUALCRYSTAL_H
