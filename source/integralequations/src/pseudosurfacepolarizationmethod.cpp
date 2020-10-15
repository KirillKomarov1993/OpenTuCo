#include "pseudosurfacepolarizationmethod.h"

namespace tuco {

MatrixXd PseudoSurfacePolarizationEquation::getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2)
{
    MatrixXd matrix = MatrixXd::Zero(_particle1->getElementCount(), _particle2->getElementCount());
    kappa_ = 2.0 * M_PI * (_particle2->getMaterial()->epsilon + environment_->getMaterial()->epsilon) /
                              (_particle2->getMaterial()->epsilon - environment_->getMaterial()->epsilon);
    for (auto &iElement1 : *_particle1->getBoundaryElements())
    {
        p =  (iElement1->getNumber() - 1);
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1);
            //matrix(p, q) = kappa * ph::kronecker(p,q) - integralSQ->getIntegral(&KernalSet::getKernal2, _particle2->getKernalSet(), iElement1, iElement2);
        }
    }
}
void PseudoSurfacePolarizationEquation::setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2)
{
    kappa_ = 2.0 * M_PI * (_particle2->getMaterial()->epsilon + environment_->getMaterial()->epsilon) /
                              (_particle2->getMaterial()->epsilon - environment_->getMaterial()->epsilon);
    for (auto &iElement1 : *_particle1->getBoundaryElements())
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1) + _q;
            //_matrix(p, q) += kappa * ph::kronecker(p,q) - integralSQ->getIntegral(&KernalSet::getKernal2, _particle2->getKernalSet(), iElement1, iElement2);
        }
    }
}
void PseudoSurfacePolarizationEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle)
{

}
void PseudoSurfacePolarizationEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field)
{
    for (auto &iElement  : *_particle->getBoundaryElements())
    {
       _vector(iElement->getNumber() - 1 + _p) += -_field->getElectricPotential(iElement->getBarycenter(), _particle->getPosition()).scalar;
    }
}

}
