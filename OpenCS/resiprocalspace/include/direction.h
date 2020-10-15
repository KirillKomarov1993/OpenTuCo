#ifndef DIRECTION_H
#define DIRECTION_H

#include "wavevector.h"

namespace cs {

struct Direction
{
    int numWaveVectors;
    std::string name;
    std::vector<WaveVector> direction;
    Direction(std::string _name);
    void setElement(WaveVector _waveVector);
    void setElements(std::vector<WaveVector> _waveVectors);
    void record(std::string _address);
    std::vector<WaveVector>* getWaveVectors()
    {
        return &direction;
    }
};

}

#endif // DIRECTION_H
