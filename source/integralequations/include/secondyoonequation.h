#ifndef SECONDYOONEQUATION_H
#define SECONDYOONEQUATION_H

#include <bem/integralequation.h>

struct SecondYoonEquation : public IntegralEquation
{
    Integration* integralMC;
    SecondYoonEquation(Integration* _integralSQ, Integration* _integralMC) :
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


#endif // SECONDYOONEQUATION_H
