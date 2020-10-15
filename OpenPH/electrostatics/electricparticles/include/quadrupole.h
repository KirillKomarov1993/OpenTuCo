#ifndef QUADRUPOLE_H
#define QUADRUPOLE_H

#include "electricparticle.h"
#include "coulombkernal.h"
#include "greenkernal.h"

namespace ph {

struct Quadrupole : public ElectricParticle
{
    Quadrupole(int _number);
    Quadrupole(int _number, Vector3d _r);
    Quadrupole(int _number, Matrix3d _Q, Vector3d _r);
    ~Quadrupole();
    void clear();
    Matrix3d* getValue()
    {
        return &Q;
    }
    ElectricPotential getElectricPotential(Vector3d _r);
    ElectricPotential getElectricPotential(Vector3d _r, GreenKernel* _kernel);
    ElectricStrength getElectricStrength(Vector3d _r);
    ElectricStrength getElectricStrength(Vector3d _r, GreenKernel* _kernel);
protected:
    Matrix3d Q;
};

}

#endif // QUADRUPOLE_H
