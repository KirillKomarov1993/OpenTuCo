#ifndef SURFACEPOLARIZATIONEQUATION_H
#define SURFACEPOLARIZATIONEQUATION_H

#include "integralequation.h"
#include "coulombkernal.h"

namespace tuco {

struct SurfacePolarizationEquation : public IntegralEquation
{   
    SurfacePolarizationEquation(std::string _type, Integration* _integralSQ, Integration* _integralMC);
    MatrixXd getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2);
    void setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2);
    void setColumnVector(int _p,VectorXd& _vector, MacroParticle* _particle);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field);
private:
    std::string type_;
    Integration* integralMC;
};


struct ExtendedSurfacePolarizationEquation : public IntegralEquation
{
    ExtendedSurfacePolarizationEquation(std::string _type, Integration* _integralSQ, Integration* _integralMC);
    MatrixXd getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2);
    void setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2);
    void setColumnVector(int _p,VectorXd& _vector, MacroParticle* _particle);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field);
private:
    std::string type_;
    Integration* integralMC;
};

/*
struct SurfacePolarizationEquationNEW : public IntegralEquation
{
    SurfacePolarizationEquationNEW(Integration* _integralSQ, Integration* _integralMC);
    MatrixXd getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2);
    void setMatrixElement(int _p, int _q, MatrixXd& _matrix, MacroParticle* _particle1, MacroParticle* _particle2);
    void setColumnVector(VectorXd& _vector);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field);
private:
     Integration* integralMC;
  //*Дополнительные функции:

};
*/
}

#endif // SURFACEPOLARIZATIONEQUATION_H
