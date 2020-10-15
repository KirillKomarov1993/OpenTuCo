/************************************************
 * Module: energyelementmethod.h
 * Author: Kirill A. Komarov
 * Modified: 11 Feb 2019 /
 * Purpose: Declaration of the class EnergyElementMethod
*************************************************/

#ifndef ENERGYELEMENTMETHOD_H
#define ENERGYELEMENTMETHOD_H

#include "integralequation.h"
#include "surfaceenergyequation.h"
#include "homogemiusfield.h"
#include "tucomethod.h"

/************************************************
* Метод расчитывает энергию взаимодействия частиц
* и геометрическую плотность на элементах, минуя
* расчет поверхностной плотности электрчиеского
* заряда
*************************************************/

namespace tuco {

class EnergyElementMethod : public TuCoMethod
{
protected:
    unsigned short p_, q_;
    unsigned short coef;
    int sizeMatrix;
    bool flagMatrix;
    MatrixXd matrix;
    VectorXd value;
    VectorXd unknowns;
    DensityMatrix* nullDensityMatrix = new DensityMatrix;
    DensityMatrix* dashDensityMatrix = new DensityMatrix;
    std::shared_ptr<SurfaceEnergyEquation> equation;
//**Абсолютно виртуальные методы и функции:
    inline virtual void setElementEnergis() = 0;
    inline virtual void setColumnVector(ph::ElectricField* _field) = 0;
    virtual void computerDensityMatrix(std::function<void*(EnergyElementMethod*, unsigned short, unsigned short, MacroParticle*, MacroParticle*)> _function) = 0;
public:
    virtual void* setDashDensityBlock(unsigned short _p, unsigned short _q, MacroParticle* _macroParticle1, MacroParticle* _macroParticle2) = 0;
    virtual void* setNullDensityBlock(unsigned short _p, unsigned short _q, MacroParticle* _macroParticle1, MacroParticle* _macroParticle2) = 0;
    EnergyElementMethod(SurfaceEnergyEquation* _equation);
    EnergyElementMethod(SurfaceEnergyEquation* _equation, Environment* _environment);
    virtual ~EnergyElementMethod();
//**Реализация виртуальных методов и функций:
    void computer(ph::ElectricField* _field);
//**Абсолютно виртуальные методы и функции:
    virtual void setInteractionsMatrix() = 0;    
};

}


#endif // ENERGYELEMENTMETHOD_H
