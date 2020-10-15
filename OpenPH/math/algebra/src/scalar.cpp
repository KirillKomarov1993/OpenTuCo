#include "scalar.h"

namespace ph {

Scalar::Scalar()
{

}
Scalar::Scalar(Vector3d _r) :
     r(_r)
{
    scalar  = 0.0;
}
Scalar::Scalar(double _scalar, Vector3d _r) :
    r(_r), scalar(_scalar)
{

}
Scalar::Scalar(Scalar const& _scalar)
    : r(_scalar.r), scalar(_scalar.scalar)
{

}
Scalar::~Scalar()
{

}
Scalar& Scalar::operator=(const Scalar& right) {
    if (this == &right) {
        return *this;
    }
    scalar = right.scalar;
    r = right.r;
    return *this;
}
Scalar& Scalar::operator+=(const Scalar& _right) {
    if (r == _right.r) {
        scalar += _right.scalar;
    }
    return *this;
}
Scalar& Scalar::operator-=(const Scalar& _right) {
    if (r == _right.r) {
        scalar -= _right.scalar;
    }
    return *this;
}
const Scalar Scalar::operator+(const Scalar& _right) const {
    return Scalar(*this) += _right;
}
const Scalar Scalar::operator-(const Scalar& _right) const {
    return Scalar(*this) -= _right;
}

}
