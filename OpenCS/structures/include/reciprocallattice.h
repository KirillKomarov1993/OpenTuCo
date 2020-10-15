#ifndef RECIPROCALLATTICE_H
#define RECIPROCALLATTICE_H

#include "basis.h"

namespace cs {

struct ReciprocalLattice
{
    ReciprocalLattice(Basis* _basis)
    {
        setReciprocalBasis(_basis);
    }
    Basis* getBasis()
    {
        return basis_;
    }
private:
    double volume_;
    Basis* basis_;
//!*Функция, создающая ресипрокальный базис:
    void setReciprocalBasis(Basis* _basis)
    {
        if (_basis->getDimension() == 2) {
            volume_ = ph::getExteriorProduct(_basis->getBasisVector(1), _basis->getBasisVector(2)) / (2.0 * ph::pi());
            basis_ = new Basis(ph::cross2D(_basis->getBasisVector(1)) / volume_,
                               ph::cross2D(_basis->getBasisVector(2)) / volume_);
        }
        else if (_basis->getDimension() == 3) {
            volume_ = _basis->getBasisVector(1).dot(_basis->getBasisVector(2).cross(_basis->getBasisVector(3)));
            basis_ = new Basis(_basis->getBasisVector(2).cross(_basis->getBasisVector(3))  / volume_,
                               _basis->getBasisVector(3).cross(_basis->getBasisVector(1))  / volume_,
                               _basis->getBasisVector(1).cross(_basis->getBasisVector(2))  / volume_);
        }
    }
};

}

#endif // RECIPROCALLATTICE_H
