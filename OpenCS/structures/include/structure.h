#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <memory>

#include "lattice.h"
#include "brillouinzone.h"

namespace cs {

// Basic object:
struct Structure
{
    Structure()
    {

    }
    void setName(std::string name)
    {
        this->name_ = name;
    }
    void setLattice(Lattice *_lattice)
    {
        lattices_.push_back(_lattice);
        numLattices_++;
    }
    void setLatticeGroup(Lattice *lattice, Particle* particle)
    {
        lattices_.push_back(lattice);
        particles_[lattice] = particle;
        numLattices_++;
    }
    void setBrillouinZone()
    {
        brillouinZone = new BrillouinZone(getMainLattice()->getBravaisLattice());
    }
    unsigned long getLatticeCount()
    {
        return numLattices_;
    }
    Particle* getParticle(Lattice* lattice)
    {
        return particles_[lattice];
    }
    Lattice* getMainLattice()
    {
        for (auto& iLattice : lattices_)
        {
            if (iLattice->isMainLattice()) {
                return iLattice;
            }
        }
    }
    std::vector<Lattice*> getLattices()
    {
        return lattices_;
    }
//!*Fuction and object for creating Brillouin Zone:
    BrillouinZone* getBrillouinZone()
    {
        return brillouinZone;
    }
private:
    unsigned long numLattices_;
    std::string name_;
    std::vector<Lattice*> lattices_;
    std::map<Lattice*, Particle*> particles_;
//!*Fuction and object for creating Brillouin Zone:
    BrillouinZone* brillouinZone;
};



}




#endif // LATTICE_H
