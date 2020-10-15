#ifndef ATOMCRYSTAL_H
#define ATOMCRYSTAL_H

#include "atom.h"
#include "realcrystal.h"

namespace atom {

//! Здесь реализован паттерн "Декоратор" для объекта AtomCrystal, с помощью обертки объекта cs::Crystal:
struct AtomCrystal : public cs::RealCrystal
{
    AtomCrystal(cs::Crystal* crystal);
    ~AtomCrystal();
//**Базовые методы:
    void setAtom(Atom* atom);
    unsigned short getInCellParticleCount();
    Atom* getAtom(unsigned long id);
    Atom* getAtom(cs::Node* node);
//**Реализация абсолютно виртуальных методов <VirtualCrystal>:
    ph::Energy getUnitCellEnergy();
private:
    unsigned short numAtoms;
    ph::Energy energy_;
    std::map<unsigned long, Atom*> atomsMap;
};

}

#endif // ATOMCRYSTAL_H
