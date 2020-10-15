#ifndef SELFCONSISTENTMETHOD_H
#define SELFCONSISTENTMETHOD_H

#include "mathlist.h"
#include "dipolemodel.h"
#include "dipole.h"
#include "homogemiusfield.h"
#include "tucomethod.h"

namespace tuco {

class SelfConsistentMethod : public TuCoMethod
{
protected:
    unsigned long sizeMatrix;
    bool flagMatrix;
    Matrix3d T;
    MatrixXd matrix;
    Space* space;
    DipoleModel* model;
public:
    SelfConsistentMethod(DipoleModel* _model);
    virtual ~SelfConsistentMethod();
//**Реализация виртуальных методов:
    void setBlock(MacroParticle* _particle1, MacroParticle* _particle2);
    void computer(ph::ElectricField* _field);
//**Абсолютно виртуальные методы и функции:
    virtual void setDipoleMoment(VectorXd _p) = 0;
    virtual void setInteractionsMatrix() = 0;
    virtual VectorXd getColumnVector(ph::ElectricStrength electricStrength) = 0;
    virtual VectorXd getColumnVector(ph::ElectricField* electricStrength) = 0;
};





}

#endif // SELFCONSISTENTMETHOD_H
