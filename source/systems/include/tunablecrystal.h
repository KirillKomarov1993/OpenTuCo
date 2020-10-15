#ifndef COLLOIDCRYSTAL_H
#define COLLOIDCRYSTAL_H

#include "tunablesystem.h"
#include "crystal.h"
#include "realcrystal.h"
#include "colloid.h"
#include "virtualcrystal.h"
#include "keezomenergy.h"
#include "madelungenergy.h"
#include "hardobjectmodel.h"

namespace tuco {

//! Здесь реализован паттерн "Декоратор" для объекта ColloidCrystal, с помощью обертки объекта cs::Crystal:
struct TunableCrystal : public cs::VirtualCrystal,
                        public TunableSystem
{
    TunableCrystal(Crystal* crystal, Environment* environment);
    ~TunableCrystal();
//**Базовые методы:
    void reset(std::string type);
    unsigned short getInCellParticleCount();
    MacroParticle* getMacroParticle(cs::Node* node);
    MacroParticle* getVirtualMacroParticle(cs::Node* node);
//**Реализация виртуальных методов <TunableSystem>:
    void computerTunableEnergy();
    void computerMadelungEnergy();
    void setMacroParticle(MacroParticle* macroParticle);
//**Реализация абсолютно виртуальных методов <VirtualCrystal>:
    ph::Energy getUnitCellEnergy();
private:
    ph::Energy energy_;
};

}

#endif // COLLOIDCRYSTAL_H
