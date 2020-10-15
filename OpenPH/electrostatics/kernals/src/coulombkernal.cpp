#include "coulombkernal.h"

namespace ph {

CoulombKernal::CoulombKernal() :
    GreenKernel()
{
    index = 1;
    name = "coulomb";
}
CoulombKernal::CoulombKernal(std::string _system) :
    GreenKernel(_system)
{
    name = "coulomb";
}
double CoulombKernal::getFunction(Vector3d _P, Vector3d _Q)
{
    return  coef / (_P - _Q).norm();
}
bool CoulombKernal::isSimplyCore()
{
    return true;
}
Vector3d CoulombKernal::getGradient(Vector3d _P, Vector3d _Q)
{
    return - coef * (_P - _Q) / pow((_P - _Q).norm(), 3);
}
Matrix3d CoulombKernal::getJacobianMatrix(Vector3d _P, Vector3d _Q)
{
    double r = (_P - _Q).norm();
    Vector3d n = (_P - _Q) / r;
    return coef * (3 * ph::getKronProduct(n, n) - Matrix3d::Identity(3, 3)) / (r * r * r);
}
Matrix3d CoulombKernal::getDipoleOperator(Vector3d _P, Vector3d _Q)
{
    double r = (_P - _Q).norm();
    Vector3d n = (_P - _Q) / r;
    return coef * (3 * ph::getKronProduct(n, n) - Matrix3d::Identity(3, 3)) / (r * r * r);
}

}

