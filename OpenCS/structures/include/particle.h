#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include "energy.h"

namespace cs {

struct Particle
{
    Particle()
    {

    }
    Particle(unsigned long number, std::string name) :
        number_(number), name_(name)
    {

    }
    virtual ~Particle();
    void setEnergy(ph::Energy);
    ph::Energy getEnergy();
    unsigned long getNumber();
protected:
    unsigned long number_;
private:
    std::string name_;
    ph::Energy energy_;
};

}

#endif // PARTICLE_H
