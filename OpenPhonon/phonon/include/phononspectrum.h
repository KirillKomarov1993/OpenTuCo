#ifndef PHONONSPECTRUM_H
#define PHONONSPECTRUM_H

#include "phonon.h"

namespace phonon {

struct PhononSpectrum
{
    int numModes;
    std::vector<Moda> modes;
    PhononSpectrum();
    void setModes(std::vector<Phonon> _phonons);
    void record(std::string _address, std::string _name);
};

}

#endif // PHONONSPECTRUM_H
