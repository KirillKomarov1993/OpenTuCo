#include "colloidmodel.h"

namespace tuco {

DLVOModel::DLVOModel(Environment* _environment, double _cut) :
    cut(_cut), environment(_environment)
{
    type = "dlvo";
    gamaker = 1.0;
}
DLVOModel::~DLVOModel()
{

}
ph::Energy DLVOModel::getEnergy(MacroParticle* _particle)
{
    norm_ = (this->particle->getPosition() - _particle->getPosition()).norm();
    if (norm_ <= cut) {
        return ph::Energy(-gamaker / (12.0 * M_PI * pow(norm_, 2)));
    } else {
        return ph::Energy();
    }
}

}
