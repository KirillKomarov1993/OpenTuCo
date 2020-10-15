#ifndef CRYSTALFUNCTIONAL_H
#define CRYSTALFUNCTIONAL_H

#include "functional.h"
#include "tunablecrystal.h"
#include "crystaldeformationmethod.h"

namespace tuco {

struct CrystalFunctional : public ph::Functional
{
    CrystalFunctional(TunableCrystal* _tunableCrystal, TunableDeformationMethod* _deformationmethod);
//**Реализация абсолютно виртуальынх функций и методов:
    void setNewArgumentVector(VectorXd _argVector);
    double getFunctionalValue() final;
    VectorXd getArgumentVector() final;
    VectorXd getGradientVector() final;
private:
    int nState_;
    int nParticle_;
    Vector3d r_;
    VectorXd argVector_;
    std::shared_ptr<TunableCrystal> tunableCrystal_;
    std::shared_ptr<TunableDeformationMethod> deformationmethod_;
};

}

#endif // CRYSTALFUNCTIONAL_H
