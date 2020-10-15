#ifndef BOUNDARYELEMENTMETHOD_H
#define BOUNDARYELEMENTMETHOD_H

#include "tunablecrystal.h"
#include "integralequation.h"
#include "homogemiusfield.h"
#include "tucomethod.h"

namespace tuco {

class BoundaryElementMethod : public TuCoMethod
{
protected:
    int p, q;
    unsigned short coef1, coef2;
    int sizeMatrix;
    bool flagMatrix;
    MatrixXd matrix;
    MatrixXd matrix1;
    MatrixXd matrix2;
    MatrixXd delta;
    VectorXd value;
    std::shared_ptr<IntegralEquation> shellEquation;
    std::shared_ptr<IntegralEquation> coreEquation;
//**Абсолютно виртуальные методы и функции:
    inline virtual void setSurfaceMultipoles(VectorXd _sigma) = 0;
    inline virtual void setColumnVector(ph::ElectricField* _field) = 0;
public:
    BoundaryElementMethod(IntegralEquation* _equation);
    BoundaryElementMethod(IntegralEquation* _equation, Environment* _environment);
    BoundaryElementMethod(IntegralEquation* _shellEquation, IntegralEquation* _coreEquation, Environment* _medium);
    virtual ~BoundaryElementMethod();
//**Реализация виртуальных методов и функций:
    void computer(ph::ElectricField* _field);
//**Абсолютно виртуальные методы и функции:
    virtual void setInteractionsMatrix() = 0;    
};

}


#endif // BOUNDARYELEMENTMETHOD_H
