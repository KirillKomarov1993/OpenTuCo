#ifndef TUNABLESYSTEM_H
#define TUNABLESYSTEM_H

//#include "homogemiusfield.h"
#include "medium.h"
#include "macroparticle.h"

namespace tuco {

struct TunableSystem
{
    TunableSystem();
    TunableSystem(Environment* environment);
    virtual ~TunableSystem();
//**Базовые функции:
    void record(std::string _address)
    {
        int i = 0;
        for (auto& iParticle : macroParticles)
        {
            i++;
            iParticle.second->record(_address, "colloid_" + std::to_string(i));
        }
    }
    void clear();
    unsigned short getParticleCount();
    Environment* getEnvironment();
    Material* getEnvironmentMaterial();
    MacroParticle* getMacroParticle(unsigned long number);    
//**Виртуальыне функции:
    virtual void setMacroParticle(MacroParticle* macroParticle);
//**Абсолютно виртуальыне функции:
    virtual void computerTunableEnergy() = 0;
    virtual void computerMadelungEnergy() = 0;
protected:
    unsigned short numParticles;
    Environment* environment;
    MacroParticle* macroParticle;
    std::map<unsigned long, MacroParticle*> macroParticles;
};

}




#endif // TUNABLESYSTEM_H
