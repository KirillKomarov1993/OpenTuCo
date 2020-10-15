#include "dipolemodel.h"

namespace tuco {

DipoleModel::DipoleModel()
{

}
DipoleModel::~DipoleModel()
{

}
void DipoleModel::setMedium(Environment* environment)
{
    this->environment = environment;
}


MutualDipoleModel::MutualDipoleModel()
{

}
inline Matrix3d MutualDipoleModel::getBlockMatrix(MacroParticle* _particle1, MacroParticle* _particle2)
{
    kappa =  3.0 / (4.0 * ph::pi()) * (_particle1->getVolume()) * (_particle1->getMaterial()->epsilon / environment->getMaterial()->epsilon - 1.0) /
                                                                  (_particle1->getMaterial()->epsilon / environment->getMaterial()->epsilon + 2.0);
    if (_particle1 != _particle2) {
        return -environment->getCreenCore()->getDipoleOperator(_particle1->getPosition(), _particle2->getPosition());
    }
    else
    {
        return Matrix3d::Identity(3, 3) / kappa;
    }
}


}
