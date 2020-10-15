#include "tunablecluster.h"

namespace tuco {

TunableCluster::TunableCluster(Environment* environment) :
    TunableSystem(environment)
{

}
//**Базовые методы:
void TunableCluster::reset(std::string type)
{
    if (type == "energy") {
        for (auto& iMacroParticle1 : *getMacroParticleMap())
        {
            iMacroParticle1.second->getHamiltanian()->clear( "induced");
            iMacroParticle1.second->getHamiltanian()->clear(    "self");
            iMacroParticle1.second->getHamiltanian()->clear("external");
        }
    }
}
ph::Energy TunableCluster::getClusterEnergy()
{
    ph::Energy energy = ph::Energy();
    for (auto& iMacroParticle1 : *getMacroParticleMap())
    {
        energy.addEnergy(iMacroParticle1.second->getHamiltanian()->getEnergy());
    }
    return energy;
}
std::map<unsigned long, MacroParticle*>* TunableCluster::getMacroParticleMap()
{
    return &macroParticles;
}
//**Реализация виртуальных методов:
void TunableCluster::computerTunableEnergy()
{   
    for (auto& iMacroParticle1 : *getMacroParticleMap())
    {
        energy_ = new ph::Energy(0.0);
        for (auto& iMacroParticle2 : *getMacroParticleMap())
        {
            if (iMacroParticle1 != iMacroParticle2) {
                energy_->addEnergy(iMacroParticle1.second->getInteractionsEnergy(iMacroParticle2.second, getEnvironment()));
            }
        }
        //std::cout << iMacroParticle1.second->getSelfEnergy().getValue() << std::endl;
        iMacroParticle1.second->getHamiltanian()->setPotentialEnergy( "induced", new KeezomEnergy(new ph::Energy(*energy_)));
        iMacroParticle1.second->getHamiltanian()->setPotentialEnergy(    "self", new KeezomEnergy(new ph::Energy(iMacroParticle1.second->getSelfEnergy())));
        iMacroParticle1.second->getHamiltanian()->setPotentialEnergy("external", new KeezomEnergy(new ph::Energy(iMacroParticle1.second->getExternalEnergy(getEnvironment()->getElectricField()))));
    }    
    //std::cin.get();
}
void TunableCluster::computerMadelungEnergy()
{
    //MacroParticle* macroParticle;
    //Здесь расчет первичной энергии, исходя из заданных моделей!!! (IPL + DLVO)
    for (auto& iMacroParticle1 : *getMacroParticleMap())
    {
        for (auto& iPhysModel : *iMacroParticle1.second->getPhysicalModelMap())
        {
            energy_ = new ph::Energy();
            //iMacroParticle1.second->getHamiltanian()->clear(iPhysModel.second->getType());
            for (auto& iMacroParticle2 : *getMacroParticleMap())
            {
                if (iMacroParticle1 != iMacroParticle2) {
                    energy_->addEnergy(iPhysModel.second->getEnergy(iMacroParticle2.second));
                }
            }
            iMacroParticle1.second->getHamiltanian()->setPotentialEnergy(iPhysModel.second->getType(), new MadelungEnergy(*energy_));
        }
    }
}

}
