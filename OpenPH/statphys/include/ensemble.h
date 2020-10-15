#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include "physstate.h"

namespace ph {

struct Time
{
    Time(unsigned long _number, double _time) :
        number(_number), time(_time)
    {

    }
    unsigned long getNumber()
    {
        return  number;
    }
    double getValue() const
    {
        return time;
    }
private:
    unsigned long number;
    double time;
};

struct Interval
{
    Interval()
    {

    }
    void setTime(Time* _time)
    {
        times.push_back(*_time);
    }
    Time* getTime(unsigned long _number)
    {
        for (auto& iTime : times)
        {
            if (iTime.getNumber() == _number)
            {
                return &iTime;
            }
        }
    }
    std::vector<Time>* getTimes()
    {
        return &times;
    }
private:
    std::vector<Time> times;
};


struct Ensemble
{    
    Ensemble()
    {
        numStates = 1;
        physStates.push_back(PhysState());
    }
    void setNullPhysState(PhysState* _physstate)
    {
        physStates[0] = *_physstate;
    }
    void setPhysState(PhysState *_physstate)
    {
        physStates.push_back(*_physstate);
        numStates++;
    }
    unsigned long getPhysStateCount()
    {
        return  numStates;
    }
    PhysState* getNullPhysState()
    {
        return &physStates[0];
    }
    PhysState* getPhysState(unsigned long number)
    {
        return &physStates[number];
    }
private:
    unsigned long numStates;
    //PhysState* nullState;
    //Thermostat* thermostat;
    std::vector<PhysState> physStates;
};




/*
    void setMeanSquareDisplacement()
    {
        vector dr;
        double sum = 0.0;
        int numEvents = 0;
        for (auto itStates : ensemble)
        {
            std::cout << "            " << itStates.number << " / " << numStates << std::endl;
            for(auto itParticles : itStates.state)
            {
                dr = itParticles.r - nullState->state[itParticles.number - 1].r;
                if (dr(0) < thermostat->figure->length/2.0 && dr(1) < thermostat->figure->width/2.0) {
                    sum += dr.dot(dr);
                    numEvents++;
                    if (dr(0) > thermostat->figure->length/4.0 && dr(1) > thermostat->figure->width/4.0) {
                        std::cout << "N = " <<  itParticles.number << std::endl << std::endl;
                        std::cout << itParticles.r << std::endl << std::endl;
                        std::cout << nullState->state[itParticles.number].r << std::endl << std::endl;
                        std::cin.get();
                    }
                }
            }
        }
        msd = sum/numEvents; // this is standard division;
    }
*/
}


#endif // ENSEMBLE_H
