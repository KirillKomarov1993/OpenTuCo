#ifndef BRILLOUINZONE_H
#define BRILLOUINZONE_H

#include "direction.h"
#include "reciprocalspace.h"

namespace cs {

struct BrillouinZone
{
    BrillouinZone(BravaisLattice* _bravais);
    void setBrillouinZone(int _approxNumber);
    void setDirection(std::string _direction, int _numWaveVectors);
    void record(std::string _address, std::string _name);
    bool isBrillouinZone(WaveVector& _wave);
    Direction* getDirection(unsigned long number)
    {
        return &directions[number];
    }
    std::vector<Direction> getDirections()
    {
        return directions;
    }
private:
    int approxNumber_;
    int nWaveVector_;    
    int numWaveVectors;
    int numBasicNodes_;
    VectorXd dk_;
    ReciprocalLattice* reciprocalLattice_;
    BravaisLattice* bravais;
    std::vector<WaveVector> brillouin;
    std::vector<WaveVector> basicNodes_;
    std::vector<Direction> directions;
    std::vector<std::string> points_;
    void setReciprocalNodes();
};

}

#endif // BRILLOUINZONE_H
