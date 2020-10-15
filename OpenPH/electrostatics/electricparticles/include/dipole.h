#ifndef DIPOLE_H
#define DIPOLE_H

#include "electricparticle.h"
#include "coulombkernal.h"
#include "greenkernal.h"

namespace ph {

struct Dipole : public ElectricParticle
{
    Dipole(int _number);
    Dipole(int _number, Vector3d _p);
    Dipole(int _number, Vector3d _p, Vector3d _r);
    ~Dipole();
    void clear();
    Vector3d* getValue()
    {
        return &p;
    }
    ElectricPotential getElectricPotential(Vector3d _r);
    ElectricPotential getElectricPotential(Vector3d _r, GreenKernel* _kernel);
    ElectricStrength getElectricStrength(Vector3d _r);
    ElectricStrength getElectricStrength(Vector3d _r, GreenKernel* _kernel);
protected:
    Vector3d p;
};

}




#endif // DIPOLE_H
