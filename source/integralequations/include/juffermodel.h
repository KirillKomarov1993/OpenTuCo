#ifndef JUFFERMETHOD_H
#define JUFFERMETHOD_H

#include <bem/integralequation.h>

struct JufferEquation : public IntegralEquation
{
    double kappa2;
    double epsilon_eff1;
    double epsilon_eff2;
    Integration* integralMC;
    JufferEquation(Integration* _integralSQ, Integration* _integralMC) :
        IntegralEquation(_integralSQ), integralMC(_integralMC)
    {
        coef = 2;
        flagCharge = true;
        flagDipole = true;
    }
    Matrix getMatrixElement(Particle* _particle1, Particle* _particle2);
    void setMatrixElement(int _p, int _q, Matrix& _matrix, Particle* _particle1, Particle* _particle2);
    void setColumnVector(int _p, Vector& _vector, Particle* _particle, HomogeneousField* _field);
private:
    Integration* _integral;
};


#endif // JUFFERMETHOD_H
