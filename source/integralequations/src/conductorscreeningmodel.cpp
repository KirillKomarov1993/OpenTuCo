#include "conductorscreeningmodel.h"

namespace tuco {

ConductorScreeningModel::ConductorScreeningModel(std::string _type, Integration* _integralSQ, Integration* _integralMC) :
    IntegralEquation(_integralSQ), type_(_type), integralMC(_integralMC)
{
    coef_ = 1;
    flagCharge_ = true;
    flagDipole_ = false;
    flag = false;
}
MatrixXd ConductorScreeningModel::getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2)
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
            matrix(p, q) = kappa_ * integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
        }
    }
    return matrix;
}
/*
void ConductorScreeningModel::setMatrixElement(int _p, int _q, MatrixXd& _Matrix, MacroParticle* _particle1, MacroParticle* _particle2)
{
    kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);
    if (!flag) {
        defineAdditionMatrix(_Matrix);
    }
    setAdditionMatrix(_p, _q, _particle1, _particle2);
    //kappa_ = -(_particle2->getMaterial()->epsilon + 0.5 * environment_->getMaterial()->epsilon) /
    //                      (_particle2->getMaterial()->epsilon - environment_->getMaterial()->epsilon);

    kappa_ = -1.0;
    for (auto &iElement1 : *_particle1->getBoundaryElements())
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1) + _q;
            if (iElement1->isNearestElement(iElement2) && type_ == "shell")
            {
                _Matrix(p, q) += kappa_ * integralMC->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
            }
            else
            {
                _Matrix(p, q) += kappa_ * integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
            }
        }
        if (_particle2->existCorePhysicalMesh()) {
            for (auto &iElement2 : *_particle2->getCoreBoundaryElements())
            {
                q = (iElement2->getNumber() - 1) + _q + _particle2->getElementCount();
                if (iElement1->isNearestElement(iElement2) && type_ == "core")
                {
                    _Matrix(p, q) += kappa_ * integralMC->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                }
                else
                {
                   _Matrix(p, q) += kappa_ * integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                }
            }
        }
    }
}
*/
void ConductorScreeningModel::setMatrixElement(int _p, int _q, MatrixXd& _Matrix, MacroParticle* _particle1, MacroParticle* _particle2)
{
    kernelFunction2_ = new GreenKernelFunction(new ph::CoulombKernal);

    //std::vector<BoundaryElement*> elements = *_particle1->getBoundaryElements();
    std::vector<BoundaryElement*> elements;
    if (type_ == "shell") {
        elements = *_particle1->getBoundaryElements();
         kappa_ = -1.0;
    }
    if (type_ == "core") {
        elements = *_particle1->getCoreBoundaryElements();
         kappa_ = -1.0;
    }
    for (auto &iElement1 : elements)
    {
        p =  (iElement1->getNumber() - 1) + _p;
        for (auto &iElement2 : *_particle2->getBoundaryElements())
        {
            q = (iElement2->getNumber() - 1) + _q;
            if (iElement1->isNearestElement(iElement2) && type_ == "shell")
            {
                _Matrix(p, q) += kappa_ * integralMC->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
            }
            else
            {
                _Matrix(p, q) += kappa_ * integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
            }
        }
        if (_particle2->existSimpleCore()) {
            for (auto &iElement2 : *_particle2->getCoreBoundaryElements())
            {
                q = (iElement2->getNumber() - 1) + _q + _particle2->getElementCount();
                if (iElement1->isNearestElement(iElement2) && type_ == "core")
                {
                    _Matrix(p, q) += kappa_ * integralMC->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                }
                else
                {
                   _Matrix(p, q) += kappa_ * integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                }
            }
        }
    }
}

void ConductorScreeningModel::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle)
{
    _vector = matrix_ * _vector;
}
void ConductorScreeningModel::setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field)
{
/*
    for (auto &iElement  : *_particle->getBoundaryElements())
    {
        _vector(iElement->getNumber() - 1 + _p) = _field->getElectricPotential(iElement->getBarycenter(), _particle->getPosition()).scalar;
    }
*/
    if (type_ == "shell") {
        for (auto &iElement  : *_particle->getBoundaryElements())
        {
            _vector(iElement->getNumber() - 1 + _p) = _field->getElectricPotential(iElement->getBarycenter(), _particle->getPosition()).scalar;
        }
    }
    if (type_ == "core") {
        for (auto &iElement  : *_particle->getCoreBoundaryElements())
        {
            _vector(iElement->getNumber() - 1 + _p) = _field->getElectricPotential(iElement->getBarycenter(), _particle->getPosition()).scalar;
        }
    }
}

}
