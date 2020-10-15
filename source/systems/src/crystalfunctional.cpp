#include "crystalfunctional.h"

namespace tuco {

CrystalFunctional::CrystalFunctional(TunableCrystal* _tunableCrystal, TunableDeformationMethod* _deformationmethod) :
    tunableCrystal_(_tunableCrystal), deformationmethod_(_deformationmethod)
{
    nState_ = 1;
    nParticle_ = 1;
    argVector_ = VectorXd(3 * tunableCrystal_->getInCellParticleCount());
}
void CrystalFunctional::setNewArgumentVector(VectorXd _argVector)
{
    nParticle_ = 1;
    for (auto& iNode : *tunableCrystal_->getMainUnitCell()->getNodes())
    {
        r_ << _argVector(0 + 3 * (nParticle_ - 1)),
              _argVector(1 + 3 * (nParticle_ - 1)),
              _argVector(2 + 3 * (nParticle_ - 1));
        tunableCrystal_->getMacroParticle(iNode)->setState(new State(nState_, r_));
        nParticle_++;
    }
    nState_++;
}
double CrystalFunctional::getFunctionalValue()
{
    return tunableCrystal_->getUnitCellEnergy().getValue();
}
VectorXd CrystalFunctional::getArgumentVector()
{
    nParticle_ = 1;
    for (auto& iNode : *tunableCrystal_->getMainUnitCell()->getNodes())
    {
        r_ = tunableCrystal_->getMacroParticle(iNode)->getPosition();
        for (int alpha = 0; alpha < 3; alpha++) {
            argVector_(alpha + 3 * (nParticle_ - 1)) = r_(alpha);
        }
        nParticle_++;
    }
    return argVector_;
}
VectorXd CrystalFunctional::getGradientVector()
{
//**Здесь реализовать расчет модулей упругости:
    deformationmethod_->computerElasticModules();
    nParticle_ = 1;
    for (auto& iNode : *tunableCrystal_->getMainUnitCell()->getNodes())
    {
        r_ = tunableCrystal_->getElasticModulus()->getModule(iNode->getNumber());
        for (int alpha = 0; alpha < 3; alpha++) {
            argVector_(alpha + 3 * (nParticle_ - 1)) = r_(alpha);
        }
        nParticle_++;
    }
    return argVector_;
}

}
