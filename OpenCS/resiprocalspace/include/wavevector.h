#ifndef WAVEVECTOR_H
#define WAVEVECTOR_H

#include "mathlist.h"

namespace cs {

struct WaveVector
{
    WaveVector();
    WaveVector(int _number, VectorXd _k);
    int getNumber();
    Vector3d getPolarization();
    Vector3d getValue();
private:
    int number_;
    double norm_;
    VectorXd k_;
};

}

#endif // WAVEVECTOR_H
