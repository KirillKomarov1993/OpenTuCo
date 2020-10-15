#ifndef PSEUDOSURFACEPOLARIZATIONMETHOD_H
#define PSEUDOSURFACEPOLARIZATIONMETHOD_H

#include "integralequation.h"

namespace tuco {

struct PseudoSurfacePolarizationEquation : public IntegralEquation
{    
    PseudoSurfacePolarizationEquation(Integration* _integral) :
        IntegralEquation(_integral)
    {
        coef_ = 1;
        flagCharge_ = false;
        flagDipole_ = true;
    }
    MatrixXd getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2);
    void setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field);
};

}

#endif // PSEUDOSURFACEPOLARIZATIONMETHOD_H
