#ifndef HARDOBJECTMODEL_H
#define HARDOBJECTMODEL_H

#include "macroparticle.h"
#include "physicalmodel.h"

namespace tuco {

class HardSphereModel : public PhysicalModel
{
public:
    HardSphereModel();
    ~HardSphereModel();
    ph::Energy getEnergy(MacroParticle* _particle)
    {
        this->particle->getPosition();

        return ph::Energy();
    }
};

class InversePowerLaw : public PhysicalModel
{
    unsigned short hard_;
    double norm_;
    double amplitude_;
    double cut;
public:
    InversePowerLaw(unsigned short hard, double amplitude, double cut);
    ~InversePowerLaw();
    ph::Energy getEnergy(MacroParticle* _particle)
    {
        norm_ = (this->particle->getPosition() - _particle->getPosition()).norm();
        if (norm_ <= cut) {
            return ph::Energy(amplitude_ * pow(2.0 * particle->getShape()->getCharacteristicSize() / norm_, hard_));

        } else {
            return ph::Energy();
        }
    }
};

}

#endif // HARDOBJECTMODEL_H
