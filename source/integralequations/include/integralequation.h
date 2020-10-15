#ifndef INTEGRALEQUATION_H
#define INTEGRALEQUATION_H

#include "medium.h"
#include "macroparticle.h"
#include "integration.h"

namespace tuco {

struct DensityMatrix
{
    DensityMatrix()
    {

    }
    DensityMatrix(unsigned short _size) :
        size_(_size)
    {
        matrix_ = MatrixXd::Zero(_size, _size);
    }
    void record()
    {
        std::string fullAddress = "matrix2.txt";
        std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
        for (int p = 0; p < size_; p++)
        {
            for (int q = 0; q < size_; q++)
            {
                out << matrix_(p, q) << " ";
            }
            out << "\n";
        }
        out.close();

    }
    void setElement(unsigned short _i, unsigned short _j, double _element)
    {
        matrix_(_i, _j) = _element;
    }
    double getElement(unsigned short _i, unsigned short _j)
    {
        return matrix_(_i, _j);
    }
    MatrixXd matrix_;
protected:
    unsigned short size_;

};

struct IntegralEquation
{    
    IntegralEquation(Integration* _integral);
    virtual ~IntegralEquation();
//**Базовые функции и методы:
    void setEnvironment(Environment* _medium);
    unsigned short getEquationsSize();
    bool isChargeExist();
    bool isDipoleExist();
//**Абсолютно виртуальные методы:
    inline virtual void setMatrixElement(int, int, MatrixXd&, MacroParticle*, MacroParticle*) = 0;
    inline virtual void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle) = 0;
    inline virtual void setColumnVector(int, VectorXd&, MacroParticle*, ph::ElectricField*) = 0;    
    inline virtual MatrixXd getMatrixElement(MacroParticle*, MacroParticle*) = 0;
protected:
    int p, q;
    unsigned short coef_;
    double kappa_;
    bool flagCharge_;
    bool flagDipole_;
    Environment* environment_;
    Integration* integralSQ_;
    GreenKernelFunction* kernelFunction1_;
    GreenKernelFunction* kernelFunction2_;
};

}



#endif // INTEGRALEQUATION_H
