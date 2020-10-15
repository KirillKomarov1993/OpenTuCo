#ifndef ATOM_H
#define ATOM_H

#include <memory>

#include "mathlist.h"
#include "particle.h"
#include "atompotential.h"
#include "element.h"

namespace atom {

struct Atom : public cs::Particle {
    Atom(unsigned long number, phonon::Element* element);
    Atom(Atom* atom, Vector3d r);
    void setPosition(Vector3d position);
    void setInterPotential(unsigned long id, Potential* potential);
    unsigned long getID();
    double getMass();
    Vector3d getPosition();
    phonon::Element* getElement();
    Potential* getPotential(Atom* atom);
private:
    Vector3d position;
    phonon::Element* element_;
    std::shared_ptr<cs::Particle> particle_;
    std::map<unsigned long, Potential*> potentialMap_;
};

}

#endif // ATOM_H
