#ifndef CRYSTALDIPOLEMETHOD_H
#define CRYSTALDIPOLEMETHOD_H

#include "selfconsistentmethod.h"
#include "tunablecrystal.h"
#include "dipole.h"

namespace tuco {

class CrystalDipoleMethod : public SelfConsistentMethod
{
    TunableCrystal* crystal;
public:
    CrystalDipoleMethod(TunableCrystal* crystal, DipoleModel* method);
//**Реализация виртуальных методов и функций:
    void setDipoleMoment(VectorXd _p);
    void setInteractionsMatrix();
    VectorXd getColumnVector(ph::ElectricStrength electricStrength);
    VectorXd getColumnVector(ph::ElectricField* electricStrength);
};

}

#endif // CRYSTALDIPOLEMETHOD_H
