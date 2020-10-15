#ifndef REALCRYSTAL_H
#define REALCRYSTAL_H

#include "crystal.h"

namespace cs {

struct RealCrystal : public Crystal
{
    RealCrystal();
    RealCrystal(Crystal* crystal) :
        Crystal(*crystal)
    {

    }
    ~RealCrystal();
    void define(double);
    void record(std::string _address, std::string _name);
    void setStructure(std::shared_ptr<Structure> structure);
    void setVariation(VirtualShift* _shift);
    void removeVariation();
};

}
#endif // REALCRYSTAL_H
