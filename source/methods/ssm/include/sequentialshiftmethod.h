#ifndef SEQUENTIALSHIFTMETHOD_H
#define SEQUENTIALSHIFTMETHOD_H

#include "tunablecluster.h"
#include "tunablepotential.h"
#include "configuration.h"

namespace tuco {

class SequentialShiftMethod
{
    int nState;
    int numState;
    ph::Energy nullEnergy;
    MacroParticle* macroParticle;
    TunablePotential* tunablePotential;
    std::vector<State*> scale;
    std::vector<double> trn;
    Configurator* configuration;
protected:
    TunableCluster* tunableCluster;
public:
    SequentialShiftMethod(Configurator* configuration, TunableCluster* tunableCluster);
    virtual ~SequentialShiftMethod();
    void setLogarithmicScale(int _number1, double _x1, double _x2);
    void setDoubleLogarithmicScale(int _number1, int _number2, double _x1, double _x2, double _x3);
    void shiftTunableSystem();
    void computerPairPotential();
    void computerTunablePotential();
    TunablePotential* getTunablePotentail();
    virtual void computerTunableEnergy() = 0;
};


}

#endif // SEQUENTIALSHIFTMETHOD_H
