#ifndef CRYSTALDEFORMATIONMETHOD_H
#define CRYSTALDEFORMATIONMETHOD_H

#include "tucomethod.h"
#include "tunablecrystal.h"
#include "deformationmethod.h"
#include "rotatingelectricfield.h"

namespace tuco {

//**Реализация МОД для коллоидного кристалла с определенным типом взаимодействия (управляемого); Здесь в будущем необходимо сделать Manager + group(Builder);
class TunableDeformationMethod : public cs::InternalDeformationMethod
{
    ph::HomogeneousRotatingField* field_;
    TuCoMethod* method_;
    TunableCrystal* colloidCrystal_;
public:
    TunableDeformationMethod(TunableCrystal* colloidCrystal_,  ph::HomogeneousRotatingField* field_, TuCoMethod* method, double step);
    ~TunableDeformationMethod();
//**Реализация абсолютно виртуальных функций и методов:
    void computerCellEnergy() final;
};

}

#endif // CRYSTALDEFORMATIONMETHOD_H
