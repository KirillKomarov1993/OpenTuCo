#ifndef INTEGRALEQUATIONMETHOD_H
#define INTEGRALEQUATIONMETHOD_H


#include <bem/integralequation.h>

struct ConductorScreeningEquation : public IntegralEquation
{
    ConductorScreeningEquation(SymplexIntegration* _integral) :
        IntegralEquation(_integral)
    {
        coef = 1;
        flagCharge = true;
        flagDipole = false;
    }
    Matrix getMatrixElement(Particle* _particle1, Particle* _particle2);
    void setMatrixElement(int _p, int _q, Matrix& _matrix, Particle* _particle1, Particle* _particle2);
    void setColumnVector(int _p, Vector& _vector, Particle* _particle, HomogeneousField* _field);
};



#endif // INTEGRALEQUATIONMETHOD_H
