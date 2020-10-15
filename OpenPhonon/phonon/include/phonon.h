#ifndef PHONON_H
#define PHONON_H

#include "brillouinzone.h"

namespace phonon {

struct Phonon
{
    double omega;
    cs::WaveVector wave;
    Phonon();
    Phonon(cs::WaveVector _wave, double _omega);
};

struct Moda
{
    int number;
    int numPhonon;
    std::vector<Phonon> phonons;
    Moda(int _number);
    void setPhonon(Phonon _phonon);
    void record(std::string _address, std::string _name);
};

}

#endif // PHONON_H
