#ifndef COLLOIDMODEL_H
#define COLLOIDMODEL_H

#include "physicalmodel.h"

namespace tuco {

class DLVOModel : public PhysicalModel
{
    double gamaker;
    double norm_;
    double cut;
    Environment* environment;
public:
    DLVOModel(Environment* _environment, double _cut);
    ~DLVOModel();
    ph::Energy getEnergy(MacroParticle* _particle);
};

}

#endif // COLLOIDMODEL_H
