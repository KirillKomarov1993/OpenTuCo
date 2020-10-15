#ifndef CRYSTALELEMENTMETHOD_H
#define CRYSTALELEMENTMETHOD_H

#include "boundaryelementmethod.h"

namespace tuco {

class CrystalElementMethod : public BoundaryElementMethod
{
    TunableCrystal* crystal;
//**Реализация виртуальных методов и функций:
    void setSurfaceMultipoles(VectorXd _value);
    void setColumnVector(ph::ElectricField* _field);
public:
    CrystalElementMethod(TunableCrystal* _crystal, IntegralEquation* _equation);
//**Реализация виртуальных методов и функций:
    void setInteractionsMatrix();    
};

}
#endif // CRYSTALELEMENTMETHOD_H
