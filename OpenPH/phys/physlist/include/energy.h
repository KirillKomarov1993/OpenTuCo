#ifndef ENERGY_H
#define ENERGY_H

#include "mathlist.h"

namespace ph {

struct Energy
{    
    Energy();
    Energy(double _energy);
    ~Energy()
    {

    }
    void clear();
    void setValue(double _energy);
    void addValue(double _energy);
    void addEnergy(Energy _energy);
    void addEnergy(Energy* _energy);
    double getValue()
    {
        return energy;
    }
    Energy& operator=(const Energy& right);
    Energy& operator+=(const Energy& _right);
    Energy& operator-=(const Energy& _right);
    const Energy operator+(const Energy& _right) const;
    const Energy operator-(const Energy& _right) const;
    Energy* operator=(const Energy* right);
    const Energy operator/(const double _right) const;
    /*
    const Energy operator*(const double _right) const {
        return Energy(energy * _right, type);
    }
    */
    Energy* operator*(const double _right);
    //friend std::ostream& operator << (std::ostream& _flux, const Energy _energy);
protected:
    double energy;
};

}

#endif // ENERGY_H
