#include "yukawakernal.h"

namespace ph {

YukawaKernal::YukawaKernal(double _kappa) :
    GreenKernel(), kappa(_kappa)
{
    name = "yukawa";
}
YukawaKernal::YukawaKernal(double _kappa, std::string _system) :
    GreenKernel(_system), kappa(_kappa)
{
    name = "yukawa";
}
double YukawaKernal::getFunction(Vector3d _P, Vector3d _Q)
{
    _R = (_P - _Q).norm();
    return  coef * exp(-kappa * _R) / _R;
}
bool YukawaKernal::isSimplyCore()
{
    return true;
}
Vector3d YukawaKernal::getGradient(Vector3d _P, Vector3d _Q)
{
    _R = (_P - _Q).norm();
    return -coef * exp(-kappa * _R) / (_R * _R)  * (1.0 / _R + kappa) * (_P - _Q);
}
Matrix3d YukawaKernal::getJacobianMatrix(Vector3d _P, Vector3d _Q)
{
    _R = (_P - _Q).norm();
    Vector3d n = (_P - _Q) / _R;
    return coef * exp(-kappa * _R) * (
                (1 + kappa * _R) * (3 * getKronProduct(n, n) - Matrix3d::Identity(3, 3)) / (_R * _R * _R) +
                kappa * kappa * getKronProduct(n, n) / _R
               );
}
Matrix3d YukawaKernal::getDipoleOperator(Vector3d _P, Vector3d _Q)
{
    double r = (_P - _Q).norm();
    Vector3d n = (_P - _Q) / r;
    return coef * (
                 (1 + kappa * r) * (3 * getKronProduct(n, n) - Matrix3d::Identity(3, 3)) / (r * r * r) +
                 kappa * kappa * getKronProduct(n, n) / r
                );
}

}


