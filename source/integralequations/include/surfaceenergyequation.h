#ifndef SURFACEENERGYEQUATION_H
#define SURFACEENERGYEQUATION_H

#include "integralequation.h"
#include "coulombkernal.h"

namespace tuco {

struct SurfaceEnergyEquation : public IntegralEquation
{
    SurfaceEnergyEquation(Integration* _integralSQ, Integration* _integralMC);
    MatrixXd getMatrixElement(MacroParticle* _particle1, MacroParticle* _particle2);
    void setMatrixElement(int _p, int _q, MatrixXd& _matri, MacroParticle* _particle1, MacroParticle* _particle2);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle);
    void setColumnVector(int _p, VectorXd& _vector, MacroParticle* _particle, ph::ElectricField* _field);
    void setDensityMatrix(DensityMatrix* _matrix)
    {
        densityMatrix_= _matrix;
    }
private:
    DensityMatrix* densityMatrix_;
    Integration* integralMC;

};

}

#endif // SURFACEENERGYEQUATION_H
