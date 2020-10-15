#ifndef YUKAWAKERNAL_H
#define YUKAWAKERNAL_H

#include "greenkernal.h"

namespace ph {

struct YukawaKernal : public GreenKernel
{
    double kappa;
    YukawaKernal(double _kappa);
    YukawaKernal(double _kappa, std::string _system);
    double getFunction(Vector3d _P, Vector3d _Q);
    bool isSimplyCore();
    Vector3d getGradient(Vector3d _P, Vector3d _Q);
    Matrix3d getJacobianMatrix(Vector3d _P, Vector3d _Q);
    Matrix3d getDipoleOperator(Vector3d _P, Vector3d _Q);
private:
    double _R;
};

}

#endif // YUKAWAKERNAL_H
