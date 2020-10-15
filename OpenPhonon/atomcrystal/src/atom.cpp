#include "atom.h"

namespace atom {

Atom::Atom(unsigned long number, phonon::Element* element)
{
    this->number_ = number;
    this->element_ = element;
}
Atom::Atom(Atom* atom, Vector3d r)
{
    this->number_ = atom->getNumber();
    this->element_ = atom->getElement();
    this->setPosition(r);
}
void Atom::setPosition(Vector3d position)
{
    this->position = position;
}
void Atom::setInterPotential(unsigned long id, Potential* potential)
{
    potentialMap_[id] = potential;
}
unsigned long Atom::getID()
{
    return number_;
}
double Atom::getMass()
{
    return element_->getMass();
}
Vector3d Atom::getPosition()
{
    return position;
}
phonon::Element* Atom::getElement()
{
    return element_;
}
Potential* Atom::getPotential(Atom* atom)
{
    return potentialMap_[atom->getID()];
}

}
