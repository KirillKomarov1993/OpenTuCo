#ifndef TUNABLECLUSTER_H
#define TUNABLECLUSTER_H

#include "tunablesystem.h"
#include "keezomenergy.h"
#include "madelungenergy.h"
#include "physicalmodel.h"

namespace tuco {

struct TunableCluster : public TunableSystem
{
    TunableCluster(Environment* environment);
    ~TunableCluster()
    {
        delete elStrength;
        //delete macroParticle;
    }
//**Базовые методы:
    void reset(std::string type);
    ph::Energy getClusterEnergy();
    std::map<unsigned long, MacroParticle*>* getMacroParticleMap();
//**Реализация виртуальных методов:
    void computerTunableEnergy();
    void computerMadelungEnergy();
private:
    ph::Energy* energy_;
    ph::ElectricStrength* elStrength;
};

}

#endif // TUNABLECLUSTER_H
