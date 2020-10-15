#ifndef PHYSICALMODEL_H
#define PHYSICALMODEL_H

#include "macroparticle.h"

namespace tuco {

class PhysicalModel
{
protected:
    std::string type;
    MacroParticle* particle;
public:
    PhysicalModel();
    virtual ~PhysicalModel();
    void setMacroParticle(MacroParticle* particle)
    {
        this->particle = particle;
    }
    std::string getType()
    {
        return type;
    }
    virtual ph::Energy getEnergy(MacroParticle*) = 0;
};

}

#endif // PHYSICALMODEL_H
