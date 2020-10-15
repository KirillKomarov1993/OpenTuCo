#ifndef CONDUCTORSCREENINGMODEL_H
#define CONDUCTORSCREENINGMODEL_H

#include "integralequation.h"
#include "coulombkernal.h"

namespace tuco {

struct ConductorScreeningModel : public IntegralEquation
{
    ConductorScreeningModel(std::string _type, Integration* _integralSQ, Integration* _integralMC);
    MatrixXd getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2);
    void setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field);
private:
    bool flag;
    std::string type_;
    MatrixXd matrix_;
    VectorXd sigma_;
    Integration* integralMC;
//**Basic private functions:
    void defineAdditionMatrix(MatrixXd _matrix)
    {
        matrix_  = _matrix;
        flag = true;
    }
/*
    void setAdditionMatrix(int _p, int _q, MacroParticle* _particle1, MacroParticle* _particle2)
    {
        if (_particle1 != _particle2) {
            for (auto &iElement1 : *_particle1->getBoundaryElements())
            {
                p =  (iElement1->getNumber() - 1) + _p;
                for (auto &iElement2 : *_particle2->getBoundaryElements())
                {
                    q = (iElement2->getNumber() - 1) + _q;
                    matrix_(p, q) = integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                }
            }
        }
    }
*/
    void setAdditionMatrix(int _p, int _q, MacroParticle* _particle1, MacroParticle* _particle2)
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
        if (_particle1 != _particle2) {
            for (auto &iElement1 : elements)
            {
                p =  (iElement1->getNumber() - 1) + _p;
                for (auto &iElement2 : *_particle2->getBoundaryElements())
                {
                    q = (iElement2->getNumber() - 1) + _q;
                    if (iElement1->isNearestElement(iElement2) && type_ == "shell")
                    {
                        matrix_(p, q) = -kappa_ * integralMC->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                    }
                    else
                    {
                        matrix_(p, q) = -kappa_ * integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                    }
                }
                if (_particle2->existSimpleCore()) {
                    for (auto &iElement2 : *_particle2->getCoreBoundaryElements())
                    {
                        q = (iElement2->getNumber() - 1) + _q + _particle2->getElementCount();
                        if (iElement1->isNearestElement(iElement2) && type_ == "core")
                        {
                            matrix_(p, q) = -kappa_ * integralMC->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                        }
                        else
                        {
                            matrix_(p, q) = -kappa_ * integralSQ_->getIntegral(&KernelFunction::getKernal1, kernelFunction2_, iElement1, iElement2);
                        }
                    }
                }
            }
        }
    }

};

}

#endif // CONDUCTORSCREENINGMODEL_H
