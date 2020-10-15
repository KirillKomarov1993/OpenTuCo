#include "surfaceenergyequation.h"

namespace tuco {

SurfaceEnergyEquation::SurfaceEnergyEquation(Integration* _integralSQ, Integration* _integralMC) :
    IntegralEquation(_integralSQ), integralMC(_integralMC)
{
    coef_ = 1;
    flagCharge_ = true;
    flagDipole_ = false;
}
MatrixXd SurfaceEnergyEquation::getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2)
{
    GreenKernelFunction* kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);
    MatrixXd matrix = MatrixXd::Zero(_particle1->getElementCount(), _particle2->getElementCount());
    kappa_ = 2.0 * M_PI * (_particle2->getMaterial()->epsilon + environment_->getMaterial()->epsilon) /
                              (_particle2->getMaterial()->epsilon - environment_->getMaterial()->epsilon);
    for (auto &iElement1 : *_particle1->getBoundaryElements())
    {
        p = (iElement1->getNumber() - 1);
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1);
            matrix(p, q) = kappa_ * ph::kronecker(p, q) + integralSQ_->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
        }
    }
    return matrix;
}
void SurfaceEnergyEquation::setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2)
{
    GreenKernelFunction* kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);
    kappa_ = 2.0 * M_PI * (_particle2->getMaterial()->epsilon + environment_->getMaterial()->epsilon) /
                          (_particle2->getMaterial()->epsilon - environment_->getMaterial()->epsilon);
    for (auto &iElement1 : *_particle1->getBoundaryElements())
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1) + _q;
            //std::cout << p << "   " << q << std::endl;
            if (iElement1->isNearestElement(iElement2))
            {
                _matrix(p, q) += (static_cast<double>(_particle1 == _particle2) * kappa_  * ph::kronecker(p, q) + integralMC->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2))
                        * densityMatrix_->getElement(static_cast<unsigned short>(p), static_cast<unsigned short>(q));
            }
            else
            {
               _matrix(p, q) += integralSQ_->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2)
                        * densityMatrix_->getElement(static_cast<unsigned short>(p), static_cast<unsigned short>(q));
            }
        }
    }
}
void SurfaceEnergyEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field)
{
    double chi = 3.0 / (4.0 * M_PI) * (_particle->getMaterial()->epsilon - environment_->getMaterial()->epsilon) / (_particle->getMaterial()->epsilon + 2.0 * environment_->getMaterial()->epsilon);
    for (auto &iElement  : *_particle->getBoundaryElements())
    {
        p =  (iElement->getNumber() - 1) + _p;
       _vector(iElement->getNumber() - 1 + _p) = (1.0 / chi) * densityMatrix_->getElement(static_cast<unsigned short>(p), static_cast<unsigned short>(p));
    }
}
void SurfaceEnergyEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle)
{

}

}
