#ifndef WIENERMETHOD_H
#define WIENERMETHOD_H

/*

#include <time.h>

#include "processing.h"
#include "direction.h"

namespace pr {

class WienerMethod {
    Processing* processing;
public:
    std::vector< std::complex<double> > mode_L, mode_T;
    WienerMethod(Processing* processing);
    ~WienerMethod();
    void loadMDfile(int);

    void getFrequencyAxis();
    void getPowerSpectraDensity(cs::Direction* direction, std::string name);
    void computerPhononModes2D(cs::Direction* direction);
    void computerPhononModes2D_MPI(cs::Direction* direction);
    std::vector<double> computerSpectraBvK(std::vector<VectorXd>&, int);
};


}

*/

#endif // WIENERMETHOD_H
