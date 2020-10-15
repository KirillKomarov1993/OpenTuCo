#ifndef PARTICLEBUILDER_H
#define PARTICLEBUILDER_H

#include "macroparticle.h"

namespace tuco {

class MacroPartilceBuilder
{
public:
    MacroPartilceBuilder();
    virtual ~MacroPartilceBuilder();
    virtual void build() = 0;
    virtual void createNewCrystal() = 0;
    virtual void setProperties(Object* object) = 0;
    MacroParticle* getParticle()
    {

    }
};



}
#endif // PARTICLEBUILDER_H
