#ifndef PHYSSTATE_H
#define PHYSSTATE_H

#include "mathlist.h"
#include "materialpoint.h"

/*
struct Thermostat
{
    std::string type;
    Figure* figure;
    Thermostat(std::string _type, Figure _figure) :
        type(_type)
    {
        figure = &_figure;
    }
    Thermostat(std::string _type, Figure* _figure) :
        type(_type)
    {
        figure = _figure;
    }

};
*/

namespace ph {

struct PhysState
{
    PhysState()
    {

    }
    PhysState(int _number)
    {
        number = _number;
        numMaterialPoint = 0;
    }
    void setMaterialPoint(MaterialPoint _materialpoint)
    {
        materialpoints.push_back(MaterialPoint(_materialpoint));
        numMaterialPoint++;
    }
    void setMaterialPoint(unsigned long _numberMaterialPoint, MaterialPoint _atom)
    {
        materialpoints[_numberMaterialPoint - 1] = MaterialPoint(_atom);
        numMaterialPoint++;
    }
    unsigned long getMaterialPointCount()
    {
        return numMaterialPoint;
    }
    unsigned long getNumber()
    {
        return number;
    }
    MaterialPoint* getMaterialPoint(unsigned long _number)
    {
        return &materialpoints[_number];
    }
    std::vector<MaterialPoint>* getMaterialPoints()
    {
        return &materialpoints;
    }
protected:
    unsigned long number;
    unsigned long numMaterialPoint;
    std::vector<MaterialPoint> materialpoints;
};

}

#endif // PHYSSTATE_H
