#include "surfacepolarizationmethod.h"


Matrix SurfacePolarizationEquation::getMatrixElement(Particle* _particle1, Particle* _particle2)
{
    Matrix matrix = Matrix::Zero(_particle1->numElements, _particle2->numElements);
    kappa = 2.0 * math::pi() * (_particle2->getMaterial()->epsilon + medium->getMaterial()->epsilon) /
                              (_particle2->getMaterial()->epsilon - medium->getMaterial()->epsilon);
    for (auto &iElement1 : _particle1->elements)
    {
        p = (iElement1->getNumber() - 1);
        for (auto &iElement2 : _particle2->elements)
        {
            q = (iElement2->getNumber() - 1);
            matrix(p, q) = kappa * math::kronecker(p, q) + integralSQ->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2);
        }
    }
}
void SurfacePolarizationEquation::setMatrixElement(int _p, int _q, Matrix& _matrix, Particle* _particle1, Particle* _particle2)
{
    kappa = 2.0 * math::pi() * (_particle2->getMaterial()->epsilon + medium->getMaterial()->epsilon) /
                               (_particle2->getMaterial()->epsilon - medium->getMaterial()->epsilon);
    for (auto &iElement1 : _particle1->elements)
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : _particle2->elements)
        {
            q = (iElement2->getNumber() - 1) + _q;
            if (iElement1->isNearestElement(iElement2))
            {
                _matrix(p, q) += (double)(_particle1 == _particle2) * kappa  * math::kronecker(p, q) + integralMC->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2);
            }
            else
            {
               _matrix(p, q) += integralSQ->getIntegral(&KernalSet::getPseudoKernal2, _particle2->getKernalSet(), iElement1, iElement2);
            }
        }
    }
}
void SurfacePolarizationEquation::setColumnVector(int _p, Vector& _vector, Particle* _particle, HomogeneousField* _field)
{
    for (auto &iElement  : _particle->elements)
    {
       _vector(iElement->getNumber() - 1 + _p) = -_field->getElectricField(iElement->getBarycenter()).strength.dot(iElement->getNormal());
    }
}

