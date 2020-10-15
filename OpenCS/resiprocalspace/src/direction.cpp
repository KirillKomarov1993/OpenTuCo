#include "direction.h"

namespace cs {

Direction::Direction(std::string _name) :
    name(_name)
{
    numWaveVectors = 0;
}
void Direction::setElement(WaveVector _waveVector)
{
    direction.push_back(_waveVector);
    numWaveVectors++;
}
void Direction::setElements(std::vector<WaveVector> _waveVectors)
{
    direction.insert(direction.end(), _waveVectors.begin(), _waveVectors.end());
    numWaveVectors += _waveVectors.size();
}
void Direction::record(std::string _address)
{
    std::string fullAddress = _address + name + ".direction";
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
    for (auto iWaveVector : direction)
    {
        out << iWaveVector.getNumber() << "   ";
        for (int i = 0; i < iWaveVector.getValue().size(); i++)
        {
            out << iWaveVector.getValue()(i) << "   ";
        }
        out << "\n";
    }
    out.close();
}

}
