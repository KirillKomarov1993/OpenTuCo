#ifndef ELECTRICPARTICLE_H
#define ELECTRICPARTICLE_H

#include "mathlist.h"
#include "potential.h"
#include "electricstrength.h"
#include "greenkernal.h"
#include "coulombkernal.h"

namespace ph {

struct ElectricParticle
{    
    ElectricParticle(int _number);
    ElectricParticle(int _number, Vector3d _r);
    virtual ~ElectricParticle();
    void setPosition(Vector3d r);
    Vector3d getPosition();
    std::string getType();
    virtual void clear() = 0;
    virtual ElectricPotential getElectricPotential(Vector3d _r) = 0;
    virtual ElectricStrength getElectricStrength(Vector3d _r) = 0;
protected:
    int number;
    std::string type;
    Vector3d r;
    GreenKernel* green;
};

}






#endif // ELECTRICPARTICLE_H
