/************************************************
 * Module: Colloid.h
 * Author: Kirill A. Komarov
 * Modified: 20 Jar 2019
 * Purpose: Declaration of the class Colloid
*************************************************/

#ifndef COLLOID_H
#define COLLOID_H

#include "macroparticle.h"
#include "potential.h"
#include "electricstrength.h"
#include "hardobjectmodel.h"
#include "symplexintegration.h"
#include "montecarlointegration.h"

namespace tuco {

struct Colloid : public MacroParticle
{
    Colloid(unsigned long number);
    Colloid(unsigned long number, Object* object);
    Colloid(unsigned long number, State* state, Object* object);
    Colloid(unsigned long number, State* state, Object* object, double angle);
//**Конструктор псевдо-копирования частицы с присвоением ей нового состояния:
    Colloid(MacroParticle* macroparticle, State* state);
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

    PhysicalMesh* getPhysicalMesh()
    {
        return physicalMesh_.get();
    }
private:
    ph::Energy energy_;
    ph::GreenKernel* greenKernel_;
    Integration* integralSQ_;
    Integration* integralMC_;
    //ph::ElectricPotential* potential_;
    //ph::ElectricStrength strength_;
};

}

#endif // COLLOID_H
