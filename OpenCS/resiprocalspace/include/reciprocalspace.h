#ifndef RECIPROCALSPACE_H
#define RECIPROCALSPACE_H

#include "wavevector.h"
#include "bravaislattice.h"

namespace cs {

struct ReciprocalSpace
{    
    ReciprocalSpace(Basis* _basis);
    ReciprocalSpace(BravaisLattice* lattice);
    void setReciprocalBasis(Basis* _basis)
    {
        basis_->setBasisVector(_basis->getBasisVector(1));
    }
    void setBasicNode();
    void record(std::string _address, std::string _name);
    std::vector<WaveVector> getBasicNodes()
    {
        return basicNodes_;
    }
private:
    int dim_;
    int numBasicNodes_;
    VectorXd k_;
    Basis* basis_;
    std::vector<WaveVector> basicNodes_;
};

}

#endif // RECIPROCALSPACE_H
