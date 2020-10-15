#ifndef BORNVONKARMAN_H
#define BORNVONKARMAN_H

#include "phononspectrum.h"
#include "dynamicsmatrix.h"

namespace phonon {

class BornVonKarman {
    int numModes;
public:
    atom::AtomCrystal* crystal;
    PhononSpectrum* spectrum;
    DynamicsMatrix* dynamics;
    BornVonKarman(atom::AtomCrystal* _crystal);
    PhononSpectrum* getPhononSpectrum();
};

}

#endif // BORNVONKARMAN_H
