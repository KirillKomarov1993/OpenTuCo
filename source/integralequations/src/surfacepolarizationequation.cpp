#include "surfacepolarizationequation.h"

namespace tuco {

SurfacePolarizationEquation::SurfacePolarizationEquation(std::string _type, Integration* _integralSQ, Integration* _integralMC) :
    IntegralEquation(_integralSQ), type_(_type), integralMC(_integralMC)
{
    coef_ = 1;
    flagCharge_ = true;
    flagDipole_ = false;
}
MatrixXd SurfacePolarizationEquation::getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2)
{
    kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);
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
void SurfacePolarizationEquation::setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2)
{
    kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);

    //std::vector<BoundaryElement*> elements = *_particle1->getBoundaryElements();
    std::vector<BoundaryElement*> elements;
    if (type_ == "shell") {
        elements = *_particle1->getBoundaryElements();
        kappa_ = 2.0 * M_PI * (_particle2->getMaterial()->epsilon + environment_->getMaterial()->epsilon) /
                              (_particle2->getMaterial()->epsilon - environment_->getMaterial()->epsilon);
    }
    if (type_ == "core") {
        elements = *_particle1->getCoreBoundaryElements();
        kappa_ = 2.0 * M_PI * (_particle1->getMaterial()->epsilon + _particle1->getCoreMaterial()->epsilon) /
                              (_particle1->getMaterial()->epsilon - _particle1->getCoreMaterial()->epsilon);
    }
    for (auto &iElement1 : elements)
    {
        p =  (iElement1->getNumber() - 1) + _p;
        //std::cout << p << std::endl;
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1) + _q;
            if (iElement1->isNearestElement(iElement2))
            {
                _matrix(p, q) += static_cast<double>(_particle1 == _particle2) * kappa_  * ph::kronecker(p, q) + integralMC->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
            }
            else
            {
               _matrix(p, q) += integralSQ_->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
            }
        }
        if (_particle2->existSimpleCore()) {
            for (auto &iElement2 : *_particle2->getCoreBoundaryElements())
            {
                q = (iElement2->getNumber() - 1) + _q + _particle2->getElementCount();
                if (iElement1->isNearestElement(iElement2))
                {
                    _matrix(p, q) += static_cast<double>(_particle1 == _particle2) * kappa_  * ph::kronecker(p, q) + integralMC->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
                }
                else
                {
                   _matrix(p, q) += integralSQ_->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
                }
            }
        }
    }
}
void SurfacePolarizationEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle)
{
    if (type_ == "shell") {
        for (auto &iElement  : *_particle->getBoundaryElements())
        {
           _vector(iElement->getNumber() - 1 + _p) = 0.0;
        }
    }
    if (type_ == "core") {
        for (auto &iElement  : *_particle->getCoreBoundaryElements())
        {
           _vector(iElement->getNumber() - 1 + _p) = 0.0;
        }
    }
}
void SurfacePolarizationEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field)
{
/*
    for (auto &iElement  : *_particle->getBoundaryElements())
    {
       _vector(iElement->getNumber() - 1 + _p) = +_field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
    }
*/
    if (type_ == "shell") {
        for (auto &iElement  : *_particle->getBoundaryElements())
        {
           _vector(iElement->getNumber() - 1 + _p) = _field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
        }
    }
    if (type_ == "core") {
        for (auto &iElement  : *_particle->getCoreBoundaryElements())
        {
           _vector(iElement->getNumber() - 1 + _p) = _field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
        }
    }
}





ExtendedSurfacePolarizationEquation::ExtendedSurfacePolarizationEquation(std::string _type, Integration* _integralSQ, Integration* _integralMC) :
    IntegralEquation(_integralSQ), type_(_type), integralMC(_integralMC)
{
    coef_ = 1;
    flagCharge_ = true;
    flagDipole_ = false;
}
MatrixXd ExtendedSurfacePolarizationEquation::getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2)
{
    kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);
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
void ExtendedSurfacePolarizationEquation::setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2)
{
    kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);

    //std::vector<BoundaryElement*> elements = *_particle1->getBoundaryElements();
    std::vector<BoundaryElement*> elements;
    if (type_ == "shell") {
        elements = *_particle1->getBoundaryElements();
        kappa_ = 2.0 * M_PI * (_particle2->getMaterial()->epsilon + environment_->getMaterial()->epsilon) /
                              (_particle2->getMaterial()->epsilon - environment_->getMaterial()->epsilon);
    }
    if (type_ == "core") {
        elements = *_particle1->getCoreBoundaryElements();
        kappa_ = 2.0 * M_PI * (_particle1->getMaterial()->epsilon + _particle1->getCoreMaterial()->epsilon) /
                               (_particle1->getMaterial()->epsilon - _particle1->getCoreMaterial()->epsilon);
    }
    for (auto &iElement1 : elements)
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1) + _q;
            if (iElement1->isNearestElement(iElement2))
            {
                _matrix(p, q) += static_cast<double>(_particle1 == _particle2) * kappa_  * ph::kronecker(p, q) + integralMC->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
            }
            else
            {
               _matrix(p, q) += integralSQ_->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
            }
        }
        if (_particle2->existSimpleCore()) { //! existNanoInclusionCore()

            for (auto &iNanoInclusion : *_particle2->getCoreLinker()->getNanoInclusionCore()->getNanoInclusions())
            {
                q = (iNanoInclusion->getNumber() - 1) + _q + _particle2->getElementCount();
                //_matrix(p, q) += integralSQ_->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);

            }


            for (auto &iElement2 : *_particle2->getCoreBoundaryElements())
            {
                q = (iElement2->getNumber() - 1) + _q + _particle2->getElementCount();
                if (iElement1->isNearestElement(iElement2))
                {
                    _matrix(p, q) += static_cast<double>(_particle1 == _particle2) * kappa_  * ph::kronecker(p, q) + integralMC->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
                }
                else
                {
                   _matrix(p, q) += integralSQ_->getIntegral(&KernelFunction::getPseudoKernal2, kernelFunction2_, iElement1, iElement2);
                }
            }
        }
    }
}
void ExtendedSurfacePolarizationEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle)
{

}
void ExtendedSurfacePolarizationEquation::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field)
{
/*
    for (auto &iElement  : *_particle->getBoundaryElements())
    {
       _vector(iElement->getNumber() - 1 + _p) = +_field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
    }
*/
    if (type_ == "shell") {
        for (auto &iElement  : *_particle->getBoundaryElements())
        {
           _vector(iElement->getNumber() - 1 + _p) = _field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
        }
    }
    if (type_ == "core") {
        for (auto &iElement  : *_particle->getCoreBoundaryElements())
        {
           _vector(iElement->getNumber() - 1 + _p) = _field->getElectricStrength(iElement->getBarycenter()).strength.dot(iElement->getNormal());
        }
    }
}





}
