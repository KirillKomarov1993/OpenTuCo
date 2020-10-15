#ifndef HARTMANMETHOD_H
#define HARTMANMETHOD_H

#include "mathlist.h"
#include "processing.h"
#include "direction.h"

namespace pr {

struct Current {
    Current()
    {

    }
private:

};




struct VelocityAutocorrelationFunction {
    VelocityAutocorrelationFunction(ph::Ensemble* _ensemble) :
        ensemble_(_ensemble)
    {

    }
    double getTimeStepPart(ph::PhysState* _physState1, ph::PhysState* _physState2)
    {
        sum_  = 0.0;
        for (unsigned long i = 0; i < numMaterialPoints_; i++)
        {
            sum_ += _physState1->getMaterialPoint(i)->getVelocity().dot(_physState2->getMaterialPoint(i)->getVelocity());
        }
        return sum_ / numMaterialPoints_;
    }
    void computer()
    {
        double sumetion;
        numMaterialPoints_ = ensemble_->getNullPhysState()->getMaterialPointCount();
        std::cout << "Computer VAF, wait..." << std::endl;
        double norm_ = getTimeStepPart(ensemble_->getPhysState(0), ensemble_->getPhysState(0));
        //for (unsigned long p = 0; p < ensemble_->getPhysStateCount() / 2; p++)
        for (unsigned long p = 0; p < 500; p++)
        {
            std::cout << p << std::endl;
            sumetion  = 0.0;
            for (unsigned long q = 0; q < ensemble_->getPhysStateCount() / 2; q++)
            {
                sumetion += getTimeStepPart(ensemble_->getPhysState(q), ensemble_->getPhysState(q + p));
            }
            valuemap[p] = sumetion / (ensemble_->getPhysStateCount() / 2) / norm_;
        }
    }
    void record(std::string _address, std::string _name)
    {
        std::string fullAdress_T = _address + _name + ".vaf";
        std::ofstream out_T(fullAdress_T, std::ios::out | std::ios::binary);
        for (auto& iValue : valuemap)
        {
            out_T << iValue.first << "   " << iValue.second << std::endl;
        }
        out_T.close();
    }
private:
    unsigned long numMaterialPoints_;
    double sum_;
    ph::Ensemble* ensemble_;
    std::map<unsigned long, double> valuemap;
};



struct DensityCorrelationFunction {
    DensityCorrelationFunction(ph::Ensemble* _ensemble) :
        ensemble_(_ensemble)
    {

    }
/*
    void getVAF_omp(cs::WaveVector* _waveVector)
    {

        sum_ += exp(_wave->getValue().dot(_physState1->getMaterialPoint(i)->getPosition())) * exp(_wave->getValue().dot(_physState2->getMaterialPoint(i)->getPosition()));

        double sum, norm = 0.0;
        //vector vaf_vv(vafTau);
        //std::vector<ph::MaterialPoint>* materiapPoints = processing_->load()->getMaterialPoints();
    //#pragma omp parallel for reduction(+:norm) num_threads(5)
        unsigned long numParticle = 0;
        for (auto& iState : *ensemble_->getNullPhysState()->getMaterialPoints())
        {
            norm += exp(2.0 * _waveVector->getValue().dot(iState.getPosition()));
            numParticle++;
        }
    //#pragma omp parallel for private(sum) num_threads(5)
        for (unsigned long p = 0; p < vafTau; p++)
        {
            sum  = 0.0;
            for (auto iState : *ensemble_->getPhysState(p)->getMaterialPoints())
            {
                sum += iState.getPosition().dot(iState.getPosition());
            }
            vaf_vv(p) = sum / ensemble_->getPhysStateCount();
        }
        return vaf_vv / norm;
    }    
*/
    inline std::complex<double> getTimeStepPart(cs::WaveVector* _wave, ph::PhysState* _physState1, ph::PhysState* _physState2)
    {
        sum_  = 0.0;
        for (unsigned long i = 0; i < numMaterialPoints_; i++)
        {
            sum_ += exp(ph::i() * _wave->getValue().dot(_physState1->getMaterialPoint(i)->getPosition())) * exp(-ph::i() * _wave->getValue().dot(_physState2->getMaterialPoint(i)->getPosition()));
        }
        return sum_  / static_cast<double>(numMaterialPoints_);
    }
    inline std::vector<std::complex<double> > computer(cs::WaveVector* wave)
    {
        std::vector<std::complex<double> > values;
        std::complex<double> sumetion;
        numMaterialPoints_ = ensemble_->getNullPhysState()->getMaterialPointCount();
        std::cout << "Computer Structure Factor, wait..." << std::endl;
        for (unsigned long p = 0; p < ensemble_->getPhysStateCount() / 2; p++)
        {
            std::cout << p << std::endl;
            sumetion  = 0.0;
            for (unsigned long q = 0; q < ensemble_->getPhysStateCount() / 2; q++)
            {
                sumetion += getTimeStepPart(wave, ensemble_->getPhysState(q), ensemble_->getPhysState(q + p));
            }
            values.push_back(sumetion / static_cast<double>(ensemble_->getPhysStateCount() / 2));
        }
        return values;
    }
    void computer(cs::Direction* direction)
    {
        numMaterialPoints_ = ensemble_->getNullPhysState()->getMaterialPointCount();
        std::cout << "Computer Structure Factor, wait..." << std::endl;
        //for (unsigned long p = 0; p < ensemble_->getPhysStateCount() / 2; p++)
        for (auto& iWaveVector : *direction->getWaveVectors())
        {
            fftFactorMap[&iWaveVector] = ph::applyFFT(computer(&iWaveVector));
        }
    }
    void record(std::string _address, std::string _name)
    {
        std::string fullAdress_T = _address + _name + ".dcf";
        std::ofstream out_T(fullAdress_T, std::ios::out | std::ios::binary);
        for (auto& iMap: fftFactorMap)
        {
            for (auto& iValue : iMap.second)
            {
                out_T << abs(iValue) << "\t";
            }
            std::cout << std::endl;
        }
        out_T.close();
    }
private:
    unsigned long numMaterialPoints_;
    std::complex<double> sum_;
    ph::Ensemble* ensemble_;
    std::map<cs::WaveVector*, std::vector<std::complex<double> > > fftFactorMap;
};



}

#endif // HARTMANMETHOD_H
