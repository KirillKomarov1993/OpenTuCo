#include "juffermodel.h"


Matrix JufferEquation::getMatrixElement(Particle* _particle1, Particle* _particle2)
{
    Matrix matrix = Matrix::Zero(_particle1->numElements, _particle2->numElements);
    double epsilon_s  = medium->getMaterial()->epsilon;
    kappa = 2.0 * math::pi();
    for (auto &iElement1 : _particle1->elements)
    {
        p = (iElement1->getNumber() - 1);
        for (auto &iElement2 : _particle2->elements)
        {
            q = (iElement2->getNumber() - 1);
            matrix(p, q) =
                     -integralSQ->getIntegral(&KernalSet::getPseudoKernal3, _particle2->getKernalSet(), iElement1, iElement2);
            matrix(p, q + _particle2->numElements) = kappa * math::kronecker(p, q) -
                      integralSQ->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2);
            matrix(p + _particle1->numElements, q + _particle2->numElements) = kappa * math::kronecker(p, q);
                      integralSQ->getIntegral(&KernalSet::getPseudoKernal2, medium->getKernalSet(), iElement1, iElement2) * (_particle1->getMaterial()->epsilon / epsilon_s);
            matrix(p + _particle1->numElements, q) =
                      integralSQ->getIntegral(&KernalSet::getPseudoKernal3, medium->getKernalSet(), iElement1, iElement2);
        }
    }
}
void JufferEquation::setMatrixElement(int _p, int _q, Matrix& _matrix, Particle* _particle1, Particle* _particle2)
{
    epsilon_eff1 = medium->getMaterial()->epsilon / _particle1->getMaterial()->epsilon;
    epsilon_eff2 = _particle1->getMaterial()->epsilon / medium->getMaterial()->epsilon;
    kappa  = 2.0 * math::pi() * (epsilon_eff1 + 1.0) / (epsilon_eff1 - 1.0);
    kappa2 = 2.0 * math::pi() * (_particle1->getMaterial()->epsilon + medium->getMaterial()->epsilon) / (_particle1->getMaterial()->epsilon - medium->getMaterial()->epsilon);
    for (auto &iElement1 : _particle1->elements)
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : _particle2->elements)
        {
            q = (iElement2->getNumber() - 1) + _q;
            _integral = integralSQ;
            if (iElement1->isNearestElement(iElement2))
            {
                _integral = integralSQ;
            }
            _matrix(p, q) +=
                        (double)(_particle1 == _particle2) * kappa * math::kronecker(p, q) -
                            (
                                  + _integral->getIntegral(&KernalSet::getKernal2, medium->getKernalSet(), iElement1, iElement2) * epsilon_eff2
                                  - _integral->getIntegral(&KernalSet::getKernal2, _particle2->getKernalSet(), iElement1, iElement2) * (double)(_particle1 == _particle2)
                            ) / (epsilon_eff2 - 1.0);

            _matrix(p, q + _particle2->numElements) +=
                            (
                                  - _integral->getIntegral(&KernalSet::getKernal1, _particle2->getKernalSet(), iElement1, iElement2) * (double)(_particle1 == _particle2)
                                  + _integral->getIntegral(&KernalSet::getKernal1, medium->getKernalSet(), iElement1, iElement2)
                            ) / (epsilon_eff1 - 1.0);

            _matrix(p + _particle1->numElements, q + _particle2->numElements) +=
                        (double)(_particle1 == _particle2) * kappa2 * math::kronecker(p, q) +
                            (
                                  + _integral->getIntegral(&KernalSet::getPseudoKernal2, medium->getKernalSet(), iElement1, iElement2) * epsilon_eff2
                                  - _integral->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2) * (double)(_particle1 == _particle2)
                            ) / (epsilon_eff2 - 1.0);

            _matrix(p + _particle1->numElements, q) +=
                            (
                                    _integral->getIntegral(&KernalSet::getKernal3, _particle2->getKernalSet(), iElement1, iElement2) * (double)(_particle1 == _particle2)
                                  - _integral->getIntegral(&KernalSet::getKernal3, medium->getKernalSet(), iElement1, iElement2)
                            ) / (epsilon_eff2 - 1.0);

        }
    }
}
void JufferEquation::setColumnVector(int _p, Vector& _vector, Particle* _particle, HomogeneousField* _field)
{
    for (auto &iElement  : _particle->elements)
    {
       epsilon_eff1 = 1.0 / (_particle->getMaterial()->epsilon / medium->getMaterial()->epsilon);
       _vector(iElement->getNumber() - 1 + _p) = _field->getElectricPotential(iElement->getBarycenter(), _particle->getPlacement()).scalar;
       _vector(iElement->getNumber() - 1 + _particle->numElements + _p) = _field->getElectricField(iElement->getBarycenter()).strength.dot(iElement->getNormal());
    }
}
