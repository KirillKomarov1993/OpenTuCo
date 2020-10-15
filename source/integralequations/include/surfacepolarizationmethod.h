#ifndef SURFACEPOLARIZATIONMETHOD_H
#define SURFACEPOLARIZATIONMETHOD_H


#include <bem/integralequation.h>


struct SurfacePolarizationEquation : public IntegralEquation
{
    Integration* integralMC;
    SurfacePolarizationEquation(Integration* _integralSQ, Integration* _integralMC) :
        integralMC(_integralMC), IntegralEquation(_integralSQ)
    {
        coef = 1;
        flagCharge = true;
        flagDipole = false;        
    }
    Matrix getMatrixElement(Particle* _particle1, Particle* _particle2);
    void setMatrixElement(int _p, int _q, Matrix& _matrix, Particle* _particle1, Particle* _particle2);
    void setColumnVector(int _p, Vector& _vector, Particle* _particle, HomogeneousField* _field);
};


#endif // SURFACEPOLARIZATIONMETHOD_H
