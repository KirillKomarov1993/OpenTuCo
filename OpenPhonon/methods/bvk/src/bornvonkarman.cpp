#include "bornvonkarman.h"

namespace phonon {

BornVonKarman::BornVonKarman(atom::AtomCrystal* _crystal) :
    crystal(_crystal)
{
    dynamics = new DynamicsMatrix(crystal);
    numModes = dynamics->size; //! Костыль
}
PhononSpectrum* BornVonKarman::getPhononSpectrum()
{
    PhononSpectrum* spectrum = new PhononSpectrum();
    for (auto iDirection : crystal->getBrillouinZone()->getDirections())
    {
        for (auto iWaveVector : iDirection.direction)
        {
            dynamics->setMatrix(&iWaveVector);
            spectrum->setModes(dynamics->getEigenValues());
        }
    }
    return spectrum;
}

}
