#include "hardobjectmodel.h"

namespace tuco {

HardSphereModel::HardSphereModel()
{
    type = "elastic";
}
HardSphereModel::~HardSphereModel()
{

}

InversePowerLaw::InversePowerLaw(unsigned short hard, double amplitude, double cut) :
    hard_(hard), amplitude_(amplitude), cut(cut)
{
    type = "elastic";
}
InversePowerLaw::~InversePowerLaw()
{

}

}
