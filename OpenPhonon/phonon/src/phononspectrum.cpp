
#include "phononspectrum.h"

namespace phonon {

PhononSpectrum::PhononSpectrum()
{
    numModes = 0;
}
void PhononSpectrum::setModes(std::vector<Phonon> _phonons)
{
    int nModa = 0;
    for (auto iPhonon : _phonons)
    {
        if (!(modes.size() > nModa)) {
            modes.push_back(Moda(nModa));
            numModes++;
        }
        modes[nModa].setPhonon(iPhonon);
        nModa++;
    }
}

void PhononSpectrum::record(std::string _address, std::string _name)
{
    int nModa = 1;
    for (auto iModa : modes)
    {
        iModa.record(_address, _name + std::to_string(nModa));
        nModa++;
    }
}

}
