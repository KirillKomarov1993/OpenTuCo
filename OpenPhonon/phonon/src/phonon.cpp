#include "phonon.h"

namespace phonon {

Phonon::Phonon()
{

}
Phonon::Phonon(cs::WaveVector _wave, double _omega) :
    wave(_wave), omega(_omega)
{

}


Moda::Moda(int _number) :
    number(_number)
{
    numPhonon = 0;
}
void Moda::setPhonon(Phonon _phonon)
{
    phonons.push_back(_phonon);
    numPhonon++;
}
void Moda::record(std::string _address, std::string _name)
{
    std::string fullAddress = _address + _name + ".moda";
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);

    for (auto iPhonon : phonons)
    {
        for (int i = 0; i < iPhonon.wave.getValue().size(); i++)
        {
            out << iPhonon.wave.getValue()(i) << "   ";
        }
        out << iPhonon.omega << "\n";
    }
    out.close();
}

}
