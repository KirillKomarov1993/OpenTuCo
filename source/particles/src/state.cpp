#include "state.h"

namespace tuco {

State::State()
{

}
State::State(int _number, Vector3d _r) :
    number(_number), r(_r)
{
    u = Vector3d(0.0, 0.0, 0.0);
    n = Vector3d(0.0, 0.0, 0.0);
    theta_ = 0.0;
    setRotateMatrix();
    vFlag = false;
}
State::State(int _number, Vector3d _r, double _theta) :
    number(_number), r(_r), theta_(_theta)
{
    u = Vector3d(0.0, 0.0, 0.0);
    n = Vector3d(cos(theta_), sin(theta_), 0.0);
    setRotateMatrix();
    vFlag = false;
}
void State::setPosition(Vector3d _r)
{
    r = _r;
    number++;
}
void State::setVariation(Vector3d _u)
{
    u = _u;
    vFlag = true;
}
void State::resetVariation()
{
    u = Vector3d(0.0, 0.0, 0.0);
    vFlag = false;
}
void State::setRotateMatrix()
{
    /*
    R1 = Matrix3d::Identity();
    R1(0, 0) = n(0);
    R1(1, 1) = n(0);
    R1(0, 1) = n(1);
    R1(1, 0) = n(1);
    */
    R1 = ph::getRotationMatrix3D("z", theta_);
}
int State::getNumber()
{
    return number;
}
Vector3d State::getPosition()
{
    if (vFlag) {
        return r + u;
    }
    return r;
}


// New fuctions:
void State::setOrientation(Vector3d _n)
{
    n = _n;
}
Vector3d State::getOrientation()
{
    return n;
}
Matrix3d State::getRotateMatrix()
{
    return R1;
}







}
