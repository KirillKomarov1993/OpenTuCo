#ifndef DYNAMICSTRUCTUREFACTOR_H
#define DYNAMICSTRUCTUREFACTOR_H

#include "mathlist.h"
#include "processing.h"
#include "direction.h"

namespace pr {

struct FourierDisplacement
{
    FourierDisplacement(cs::WaveVector* _wave, Vector3d _u) :
        wave(_wave), u(_u)
    {

    }
    FourierDisplacement(unsigned long _number, cs::WaveVector* _wave, Vector3cd _u) :
        number(_number), wave(_wave), u(_u)
    {

    }
    void setDisplacements(Vector3d _u)
    {
        u = _u;
    }
    unsigned long getNumber()
    {
        return number;
    }
    Vector3cd getValue()
    {
        return u;
    }
    cs::WaveVector* getWave()
    {
        return wave;
    }
private:
    unsigned long number;
    cs::WaveVector* wave;
    Vector3cd u;
};

struct FourierState
{
    FourierState(unsigned long _number) :
        number(_number)
    {

    }
    void setFourierDisplacement(FourierDisplacement* state)
    {
        displacements.push_back(state);
    }
    unsigned long getNumber()
    {
        return number;
    }
    std::vector<FourierDisplacement*>* getFourierDisplacements()
    {
        return &displacements;
    }
private:
    unsigned long number;
    std::vector<FourierDisplacement*> displacements;
};

struct FourierEnsemble
{
    FourierEnsemble(ph::Ensemble* _ensemble, cs::Direction* _direction) :
        ensemble(_ensemble), direction(_direction)
    {

    }
    void setFourierEnsemble()
    {
        states.resize(ensemble->getPhysStateCount());
    #pragma omp parallel for num_threads(5)
        for (unsigned long q = 1; q < ensemble->getPhysStateCount(); q++)
        {
            //std::cout << q << std::endl;
            setFourierState(ensemble->getPhysState(q));
        }
    }
    void setFourierState(ph::PhysState* _physstate)
    {
        Vector3d r0, uq;
        states[_physstate->getNumber()] = new FourierState(_physstate->getNumber());
        for (auto& iWave : *direction->getWaveVectors())
        {
            uq << 0.0, 0.0, 0.0;
            for (auto iPoint : *_physstate->getMaterialPoints())
            {
                r0 = ensemble->getNullPhysState()->getMaterialPoint(iPoint.getNumber())->getPosition();
                uq += (iPoint.getPosition() - r0) * exp(iWave.getValue().dot(r0));
            }
            states[_physstate->getNumber()]->setFourierDisplacement(new FourierDisplacement(&iWave, uq));
        }
    }
    FourierState* getFourierState(unsigned long number)
    {
        return states[number];
    }
    std::vector<FourierState*>* getFourierStates()
    {
        return &states;
    }
private:
    //Vector3d r0, uq;
    cs::Direction* direction;
    ph::Ensemble* ensemble;
    std::vector<FourierState*> states;
};

//**It's function by wave vector that used in the Dynamic Structure Factor.
//**It is OMP!!!
struct FourierDynamicDisplacement
{
    FourierDynamicDisplacement(cs::WaveVector* _wave, ph::Ensemble* _ensemble) :
        wave(_wave)
    {
        setFourierDisplacements(_ensemble);
    }
    std::vector<FourierDisplacement*>* getFourierDisplacements()
    {
        return &displacements;
    }
private:
    cs::WaveVector* wave;
    std::vector<FourierDisplacement*> displacements;
//**Basic functions & methods:
    void setFourierDisplacements(ph::Ensemble* _ensemble)
    {
        displacements.resize(_ensemble->getPhysStateCount());
    #pragma omp parallel for num_threads(6)
        for (unsigned long q = 0; q < _ensemble->getPhysStateCount(); q++)
        {
            Vector3d r0;
            Vector3cd uq; uq << 0.0, 0.0, 0.0;
            //std::cout << q << std::endl;
            for (auto iPoint : *_ensemble->getPhysState(q)->getMaterialPoints())
            {
                r0 = _ensemble->getNullPhysState()->getMaterialPoint(iPoint.getNumber())->getPosition();
                uq += (iPoint.getPosition() - r0) * exp(ph::i() * wave->getValue().dot(r0));
            }
            displacements[q] = new FourierDisplacement(q, wave, uq);
        }
    }
};

struct FourierDynamicWave
{
    FourierDynamicWave(cs::Direction* _direction, ph::Ensemble* _ensemble) :
        direction(_direction)
    {
        setFourierDynamicDisplacements(_ensemble);
    }
    void setFourierDynamicDisplacements(ph::Ensemble* _ensemble)
    {
        for (auto& iWave : *direction->getWaveVectors())
        {
            displacements.push_back(new FourierDynamicDisplacement(&iWave, _ensemble));
        }
    }
    std::vector<FourierDynamicDisplacement*>* getFourierDynamicDisplacements()
    {
        return &displacements;
    }
private:
    cs::Direction* direction;
    std::vector<FourierDynamicDisplacement*> displacements;
};


struct JacksonKernel
{
    JacksonKernel(unsigned long _numPoints) :
        numPoints_(_numPoints)
    {
        amplitude_ = sqrt(2.0 / (numPoints_ + 1.0));
        period_ = 2.0 * numPoints_ / ph::pi();
    }
    double getCoeffisient(unsigned long _k)
    {
        return amplitude_ * cos(_k / period_);
    }
private:
    unsigned long numPoints_;
    double amplitude_;
    double period_;
};

struct DynamicStructureFactor
{
    DynamicStructureFactor(cs::Direction* _direction, ph::Ensemble* _ensemble)
    {
        dynamicwave = new FourierDynamicWave(_direction, _ensemble);
        kernel = new JacksonKernel(_ensemble->getPhysStateCount());
        stepTime = 1e-2;
        maxOmega = 1.0 / stepTime;
        deltaOmega = 1.0 / (_ensemble->getPhysStateCount() * stepTime);
    }
    void computer()
    {
        Vector3cd sum;
        int s = 0;
        for (auto& iFDDisplacement : *dynamicwave->getFourierDynamicDisplacements())
        {
            std::cout << s << std::endl;
            std::map<double, std::complex<double> > factorMap;
            for (double omega = 0; omega < maxOmega; omega = omega + deltaOmega)
            {
                sum << 0.0, 0.0, 0.0;
                for (auto iDisplacement : *iFDDisplacement->getFourierDisplacements())
                {
                    phi = 2.0 * asin(omega * stepTime / 2.0);
                    sum += kernel->getCoeffisient(iDisplacement->getNumber()) * iDisplacement->getValue() * sin(iDisplacement->getNumber() * phi);
                }
                factorMap[omega] = omega * omega * sum.dot(sum);
            }
            factors.push_back(factorMap);
            s++;
        }
    }
    void record(std::string _address, std::string _name)
    {
        std::string fullAdress_T = _address + _name + ".dsf";
        std::ofstream out(fullAdress_T, std::ios::out | std::ios::binary);
        for (auto& iMap: factors)
        {
            for (auto& iValue : iMap)
            {
                out << iValue.second.real() << "\t";
            }
            out << std::endl;
        }
        out.close();
    }
private:
    double phi;
    double maxOmega;
    double deltaOmega;
    double stepTime;
    JacksonKernel* kernel;
    FourierDynamicWave* dynamicwave;
    std::vector<std::map<double, std::complex<double> > > factors;
};

}

#endif // DYNAMICSTRUCTUREFACTOR_H
