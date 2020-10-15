#include "atomcrystal.h"

namespace atom {

AtomCrystal::AtomCrystal(Crystal* crystal) :
    RealCrystal(crystal)
{

}
AtomCrystal::~AtomCrystal()
{

}
unsigned short AtomCrystal::getInCellParticleCount()
{
    unsigned short nParticle = 1;
    for (auto& iNode : *getMainUnitCell()->getNodes())
    {
        nParticle++;
    }
    return nParticle;
}
Atom* AtomCrystal::getAtom(unsigned long id)
{
    return atomsMap[id];
}
Atom* AtomCrystal::getAtom(cs::Node* node)
{
    if (isMainUnitCell(node)) {
        return getAtom(node->getParticle()->getNumber());
    } else {
        return new Atom(getAtom(node->getParticle()->getNumber()), node->getPosition());
    }
}
void AtomCrystal::setAtom(Atom* atom)
{
    for (auto iNode : *getMainUnitCell()->getNodes())
    {
        if (iNode->getParticle()->getNumber() == atom->getNumber()) {
            atom->setPosition(iNode->getPosition());
            atomsMap[atom->getNumber()] = atom;
        }
    }
}
ph::Energy AtomCrystal::getUnitCellEnergy()
{
    /*
    ph::Energy energy;
    for (auto iNode : *getMainUnitCell()->getNodes()) {
        energy += *getMacroParticle(iNode)->getHamiltanian()->getEnergy();
    }
    return energy;
    */
}


}
