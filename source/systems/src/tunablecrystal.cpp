#include "tunablecrystal.h"

namespace tuco {

TunableCrystal::TunableCrystal(Crystal* crystal, Environment* medium) :
    VirtualCrystal(crystal), TunableSystem (medium)
{

}
TunableCrystal::~TunableCrystal()
{

}
void TunableCrystal::reset(std::string type)
{
    if (type == "energy") {
        for (auto& iNode1 : *getMainUnitCell()->getNodes())
        {
            macroParticle = getMacroParticle(iNode1);
            macroParticle->getHamiltanian()->clear( "induced");
            macroParticle->getHamiltanian()->clear(    "self");
            macroParticle->getHamiltanian()->clear("external");
        }
    }
}
unsigned short TunableCrystal::getInCellParticleCount()
{
    unsigned short nParticle = 1;
    for (auto& iNode : *getMainUnitCell()->getNodes())
    {
        nParticle++;
    }
    return nParticle;
}
void TunableCrystal::computerTunableEnergy()
{
    energy_ = ph::Energy(0.0);
    for (auto& iNode1 : *getMainUnitCell()->getNodes())
    {
        macroParticle = getMacroParticle(iNode1);
        for (auto& iNode2 : *getMainUnitCell()->getNodes())
        {
            if (iNode1 != iNode2) {
                energy_.addEnergy(macroParticle->getInteractionsEnergy(getMacroParticle(iNode2), getEnvironment()));
            }
        }
        for (auto& iCell : getUnitCells())
        {
            for (auto& iVirtualNode : *iCell->getNodes())
            {
                energy_.addEnergy(macroParticle->getInteractionsEnergy(getMacroParticle(iVirtualNode), getEnvironment()));
            }
        }
        macroParticle->getHamiltanian()->setPotentialEnergy( "induced", new KeezomEnergy(new ph::Energy(energy_)));
        macroParticle->getHamiltanian()->setPotentialEnergy(    "self", new KeezomEnergy(new ph::Energy(macroParticle->getSelfEnergy())));
        macroParticle->getHamiltanian()->setPotentialEnergy("external", new KeezomEnergy(new ph::Energy(macroParticle->getExternalEnergy(getEnvironment()->getElectricField()))));
        //std::cout << macroParticle->getHamiltanian()->getEnergy()->getValue() << std::endl;
    }
}
void TunableCrystal::computerMadelungEnergy()
{
    //Здесь расчет первичной энергии, исходя из заданных моделей!!! (IPL + DLVO)
    //MacroParticle* macroParticle;

    for (auto& iNode1 : *getMainUnitCell()->getNodes())
    {
        macroParticle = getMacroParticle(iNode1);

        for (auto& iPhysModel : *macroParticle->getPhysicalModelMap())
        {
            energy_ = ph::Energy();
            macroParticle->getHamiltanian()->clear(iPhysModel.second->getType());
            for (auto& iNode2 : *getMainUnitCell()->getNodes())
            {
                if (iNode1 != iNode2) {
                    energy_.addEnergy(iPhysModel.second->getEnergy(getMacroParticle(iNode2)));
                }
            }
            for (auto& iCell : getUnitCells())
            {
                for (auto& iVirtualNode : *iCell->getNodes())
                {
                    energy_.addEnergy(iPhysModel.second->getEnergy(getMacroParticle(iVirtualNode)));
                }
            }
            macroParticle->getHamiltanian()->setPotentialEnergy(iPhysModel.second->getType(), new MadelungEnergy(energy_));
        }
        //std::cout << macroParticle->getHamiltanian()->getEnergy()->getValue() << std::endl;
    }
}
MacroParticle* TunableCrystal::getMacroParticle(cs::Node* node)
{
    if (isMainUnitCell(node)) {
        return TunableSystem::getMacroParticle(node->getParticle()->getNumber());
    } else {
        return new Colloid(TunableSystem::getMacroParticle(node->getParticle()->getNumber()), new State(1, node->getPosition()));
    }
}
MacroParticle* TunableCrystal::getVirtualMacroParticle(cs::Node* node)
{
    return new Colloid(TunableSystem::getMacroParticle(node->getParticle()->getNumber()), new State(1, node->getPosition()));
}
void TunableCrystal::setMacroParticle(MacroParticle* macroParticle)
{
    for (auto iNode : *getMainUnitCell()->getNodes())
    {
        if (iNode->getParticle()->getNumber() == macroParticle->getNumber()) {
            macroParticle->setState(new State(1, iNode->getPosition()));
            macroParticles[macroParticle->getNumber()] = macroParticle;
        }
    }
}
ph::Energy TunableCrystal::getUnitCellEnergy()
{
    ph::Energy energy;
    for (auto iNode : *getMainUnitCell()->getNodes()) {
        energy += *getMacroParticle(iNode)->getHamiltanian()->getEnergy();
    }
    return energy;
}

}
