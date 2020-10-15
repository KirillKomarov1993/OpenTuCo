#include "secondyoonequation.h"


Matrix SecondYoonEquation::getMatrixElement(Particle* _particle1, Particle* _particle2)
{
    Matrix matrix = Matrix::Zero(_particle1->numElements, _particle2->numElements);
    double epsilon_s  = medium->getMaterial()->epsilon;
    double epsilon_eff = (_particle1->getMaterial()->epsilon / epsilon_s);
    kappa = 2.0 * math::pi() * (epsilon_eff - 1.0);
    for (auto &iElement1 : _particle1->elements)
    {
        p = (iElement1->getNumber() - 1);
        for (auto &iElement2 : _particle2->elements)
        {
            q = (iElement2->getNumber() - 1);
            if (_particle1 != _particle2)
            {
                matrix(p, q) =
                         0.0;
                matrix(p, q + _particle2->numElements) =
                       -(integralSQ->getIntegral(&KernalSet::getKernal1, medium->getKernalSet(), iElement1, iElement2) + epsilon_eff * integralSQ->getIntegral(&KernalSet::getKernal1, medium->getKernalSet(), iElement1, iElement2));
                matrix(p + _particle1->numElements, q + _particle2->numElements) =
                         integralSQ->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2) + integralSQ->getIntegral(&KernalSet::getPseudoKernal2, medium->getKernalSet(), iElement1, iElement2);
                matrix(p + _particle1->numElements, q) =
                         integralSQ->getIntegral(&KernalSet::getPseudoKernal3, _particle2->getKernalSet(), iElement1, iElement2) + integralSQ->getIntegral(&KernalSet::getPseudoKernal3, medium->getKernalSet(), iElement1, iElement2);
            }
            else
            {
                matrix(p, q) =
                         integralSQ->getIntegral(&KernalSet::getKernal2, _particle2->getKernalSet(), iElement1, iElement2) + integralSQ->getIntegral(&KernalSet::getKernal2, medium->getKernalSet(), iElement1, iElement2);
                matrix(p, q + _particle2->numElements) =
                       -(integralSQ->getIntegral(&KernalSet::getKernal1, _particle2->getKernalSet(), iElement1, iElement2) + epsilon_eff * integralSQ->getIntegral(&KernalSet::getKernal1, medium->getKernalSet(), iElement1, iElement2));
                matrix(p + _particle1->numElements, q + _particle2->numElements) = kappa * math::kronecker(p, q) +
                         integralSQ->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2) + integralSQ->getIntegral(&KernalSet::getPseudoKernal2, medium->getKernalSet(), iElement1, iElement2);
                matrix(p + _particle1->numElements, q) =
                         integralSQ->getIntegral(&KernalSet::getPseudoKernal3, _particle2->getKernalSet(), iElement1, iElement2) + integralSQ->getIntegral(&KernalSet::getPseudoKernal3, medium->getKernalSet(), iElement1, iElement2);
            }
        }
    }
}
void SecondYoonEquation::setMatrixElement(int _p, int _q, Matrix& _matrix, Particle* _particle1, Particle* _particle2)
{
    double epsilon_eff = _particle1->getMaterial()->epsilon / medium->getMaterial()->epsilon;
    kappa = 2.0 * math::pi();
    for (auto &iElement1 : _particle1->elements)
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : _particle2->elements)
        {
            _integral = integralSQ;
            q = (iElement2->getNumber() - 1) + _q;
            if (iElement1->isNearestElement(iElement2))
            {
                _integral = integralMC;
            }
            _matrix(p, q) +=
                             (double)(_particle1 == _particle2) * (
                                  - _integral->getIntegral(&KernalSet::getKernal3, _particle2->getKernalSet(), iElement1, iElement2)
                                                                  );
            _matrix(p, q + _particle2->numElements) +=
                             (double)(_particle1 == _particle2) * (
                                    kappa * math::kronecker(p, q)
                                  - _integral->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2)
                                                                  );
            _matrix(p + _particle1->numElements, q + _particle2->numElements) +=
                             ((double)(_particle1 == _particle2) * (
                                    kappa * math::kronecker(p, q)
                                                                   )
                                  + _integral->getIntegral(&KernalSet::getPseudoKernal2, medium->getKernalSet(), iElement1, iElement2)) * epsilon_eff;
            _matrix(p + _particle1->numElements, q) +=
                                  +  _integral->getIntegral(&KernalSet::getKernal3, medium->getKernalSet(), iElement1, iElement2);
        }
    }
}
void SecondYoonEquation::setColumnVector(int _p, Vector& _vector, Particle* _particle, HomogeneousField* _field)
{
    for (auto &iElement  : _particle->elements)
    {
       _vector(iElement->getNumber() - 1 + _p) = _field->getElectricField(iElement->getBarycenter()).strength.dot(iElement->getNormal());
       _vector(iElement->getNumber() - 1 + _particle->numElements + _p) = -_field->getElectricField(iElement->getBarycenter()).strength.dot(iElement->getNormal());
    }
}
