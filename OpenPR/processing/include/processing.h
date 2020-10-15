#ifndef PROCESSING_H
#define PROCESSING_H

#include "mathlist.h"
#include "physstate.h"
#include "ensemble.h"
#include "wavevector.h"
#include "direction.h"

namespace pr {

class Processing {

protected:
    unsigned long  nFile;
    unsigned long  stepFile;
    unsigned long  countFile;
    unsigned long numParticles;
    double stepTime;
    std::string fullAddress;
    std::string namePackage;
    ph::Ensemble* ensemble;
public:    
    Processing(std::string _namePocket, std::string _fullAddress);
    void resetPhysState()
    {
        nFile = 0;
    }
    void shiftPhysState()
    {
        nFile = nFile + stepFile;
    }
    unsigned long getFileStep()
    {
        return stepFile;
    }
    unsigned long getFileCount()
    {
        return countFile;
    }
    double getTimeStep()
    {
        return stepTime;
    }
    virtual void setHeader(std::fstream &F) = 0;
    virtual ph::PhysState* load() = 0;
    virtual ph::MaterialPoint* load(cs::WaveVector* wave) = 0;
    virtual void fineTuning(unsigned long _step, unsigned long _countFile) = 0;
};

class ProcessingLammps : public Processing {
    Vector3d r0;
    Vector3d uq;
    Vector3d vq;
    Vector3d r;
    Vector3d v;
    ph::PhysState* nullPhysState;
    ph::PhysState* physstate;
public:
    ProcessingLammps(std::string _fullAddress);
    void setEnsemble();
    void setFourierEnsemble(cs::Direction* direction);
    ph::Ensemble* getEnsemble()
    {
        return ensemble;
    }
//!*Реализауия виртуальных функций:
    void setHeader(std::fstream &F);    
    void fineTuning(unsigned long _step, unsigned long _countFile);
    ph::PhysState* load();
    ph::MaterialPoint* load(cs::WaveVector* wave);
};

}

#endif // PROCESSING_H
