#ifndef COULOMBKERNAL_H
#define COULOMBKERNAL_H

#include "greenkernal.h"

namespace ph {

struct CoulombKernal : public GreenKernel
{
    CoulombKernal();
    CoulombKernal(std::string _system);
    double getFunction(Vector3d _P, Vector3d _Q);
    bool isSimplyCore();
    Vector3d getGradient(Vector3d _P, Vector3d _Q);
    Matrix3d getJacobianMatrix(Vector3d _P, Vector3d _Q);
    Matrix3d getDipoleOperator(Vector3d _P, Vector3d _Q);
};

}

#endif // COULOMBKERNAL_H
