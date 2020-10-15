#include "lattice.h"

namespace cs {

Lattice::Lattice(std::string _flag, BravaisLattice* _bravais, Vector3d _r) :
    flag_(_flag == "main"), r_(_r), bravais_(_bravais)
{

}
double Lattice::getTranslation()
{
    return bravais_->getTranslation();
}
bool Lattice::isMainLattice()
{
    return flag_;
}
Vector3d Lattice::getNodePosition(Vector3d _n)
{
    return r_ + bravais_->getBasis()->a[0] * _n(0) + bravais_->getBasis()->a[1] * _n(1);
}
Vector3d Lattice::getPosition()
{
    return r_;
}

}
