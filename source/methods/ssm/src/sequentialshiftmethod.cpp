#include "sequentialshiftmethod.h"

namespace tuco {

SequentialShiftMethod::SequentialShiftMethod(Configurator* configurator, TunableCluster* tunableCluster)
{
    this->tunableCluster = tunableCluster;
    this->configuration = configurator;
    tunablePotential = new TunablePotential;
}
SequentialShiftMethod::~SequentialShiftMethod()
{

}
void SequentialShiftMethod::setLogarithmicScale(int _number1, double _x1, double _x2)
{
    trn.push_back(1e5);
    numState = 0;
    for (int i = 0; i < _number1; i++) {
        trn.push_back(_x1 * pow(_x2 / _x1, i / (double)(_number1 - 1)));
        numState++;
    }
}
void SequentialShiftMethod::setDoubleLogarithmicScale(int _number1, int _number2, double _x1, double _x2, double _x3)
{
    trn.push_back(1e5);
    numState = 0;
    for (int i = 0; i < _number1; i++) {
        trn.push_back(_x1 * pow(_x2 / _x1, i / (double)_number1));
        numState++;
    }
    for (int i = 0; i < _number2; i++) {
        trn.push_back(_x2 * pow(_x3 / _x2, i / (double)(_number2 - 1)));
        numState++;
    }
}
void SequentialShiftMethod::shiftTunableSystem()
{
    for (unsigned long nParticle = 1; nParticle <= configuration->getParticleCount(); nParticle++) {
        tunableCluster->getMacroParticle(nParticle)->setState(new State(nState, trn[nState] * configuration->getCoordinate(nParticle)));
    }
}
void SequentialShiftMethod::computerTunablePotential()
{
//**Расчет нулевой энергии:
    nState = 0;
    shiftTunableSystem();
    computerTunableEnergy();
    nullEnergy = tunableCluster->getClusterEnergy();
    nState++;

//**Расчет потенуцила взаимодействия:
    while(nState <= numState)
    {
        std::cout << "Number of the calculation: " << nState << " / " << numState << std::endl;
        shiftTunableSystem();
        computerTunableEnergy();
        tunablePotential->setPotentialState(trn[nState], tunableCluster->getClusterEnergy() - nullEnergy);
        nState++;
    }
}
TunablePotential* SequentialShiftMethod::getTunablePotentail()
{
    return tunablePotential;
}

}
