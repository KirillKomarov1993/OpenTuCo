#include "wavevector.h"

namespace cs {

WaveVector::WaveVector()
{

}
WaveVector::WaveVector(int _number, VectorXd _k) :
    number_(_number), k_(_k)
{
    norm_ = k_.norm();
}
int WaveVector::getNumber()
{
    return number_;
}
Vector3d WaveVector::getPolarization()
{
    return k_ / norm_;
}
Vector3d WaveVector::getValue()
{
    return k_;
}

}
