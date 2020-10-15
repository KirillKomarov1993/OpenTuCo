#ifndef DYNAMICSMATRIX_H
#define DYNAMICSMATRIX_H

#include "forcematrix.h"
#include "phonon.h"

namespace phonon {

struct DynamicsMatrix
{
    int size;
    MatrixXcd D;
    cs::WaveVector* wave;
    ForceTensor* tensor;
    atom::AtomCrystal* crystal;

    DynamicsMatrix(atom::AtomCrystal* _crystal);
    void setMatrix(cs::WaveVector* _wave);
    std::vector<Phonon> getEigenValues();
};

}

#endif // DYNAMICSMATRIX_H
