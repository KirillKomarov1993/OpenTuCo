#ifndef CSCOLLOID_H
#define CSCOLLOID_H

#include "macroparticle.h"
#include "potential.h"
#include "electricstrength.h"
#include "hardobjectmodel.h"

namespace tuco {


struct CSColloid : public MacroParticle
{
    CSColloid(unsigned long number);
    CSColloid(unsigned long number, Object* object);
    CSColloid(unsigned long number, State* state, Object* object);
//**Конструктор псевдо-копирования частицы с присвоением ей нового состояния:
    CSColloid(MacroParticle* macroparticle, State* state);
//**Базовые функции:
    void setGreenKernel(ph::GreenKernel* _greenKernel);
//**Реализауия вирутальных функций:
    void setPhysicalModel(std::string key, PhysicalModel* physicalModel);
    //!Расчет управляемой энергии:
    ph::Energy getInteractionsEnergy(MacroParticle* macroParticle, Environment* enviroment);
    ph::Energy getSelfEnergy();
    ph::Energy getExternalEnergy(ph::ElectricField* electricField);
    //!Расчет электрических полей:
    ph::ElectricPotential getElectricPotential(Vector3d r);
    ph::ElectricPotential getElectricPotential(Vector3d r, ph::GreenKernel* kernel);
    ph::ElectricStrength getElectricStrength(Vector3d r);
    ph::ElectricStrength getElectricStrength(Vector3d r, ph::GreenKernel* kernel);

private:
    ph::Energy energy_;
    ph::GreenKernel* greenKernel_;
};

}

#endif // CSCOLLOID_H
