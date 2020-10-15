#ifndef CLUSTER_H
#define CLUSTER_H

#include "particle.h"
#include "particlesystem.h"
#include "homogemiusfield.h"
#include "medium.h"
#include "stabilization.h"

namespace tuco {

struct Cluster : public TunableSystem
{
    std::vector<Colloid*> particles;
    Cluster(Medium* _medium) :
        TunableSystem("cluster", _medium)
    {
        numParticles = 0;
    }
    Cluster(std::string _type, Medium* _medium) :
        TunableSystem(_type, _medium)
    {
        numParticles = 0;
    }
    ~Cluster()
    {

    }
    void dump(std::string _address, std::string _name)
    {
        std::string fullAddress = _address + _name + ".bonds";
        std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
        for (auto &iParticle : particles)
        {
            out << iParticle->interaction << "\n";
        }
        out.close();
    }
    /*
    void setInteractions(HomogeneousField* _field)
    {
        for (auto &iParticle1 : particles)
        {
            Bond* bond  = new Bond(iParticle1->getNumber());
            bond->setEnergy("self-energy", iParticle1->getSelfEnergy());
            bond->setEnergy("external-energy", iParticle1->getExternalEnergy(_field));
            Energy energy("electric");
            for (auto &iParticle2 : particles)
            {
               if (iParticle1->number != iParticle2->number)
               {
                   energy += getInducedEnergy(iParticle1, iParticle2);
               }
            }
            bond->setEnergy("induced-energy", energy);
            iParticle1->setBond(bond);
        }
    }
    */
    void record(std::string _address, std::string _name)
    {
        for (auto &iParticle : particles)
        {
            iParticle->record(_address, _name + "n" + std::to_string(iParticle->getNumber()));
        }
    }
    void clear(std::string _gist)
    {
        if (_gist == "charge") {
            for (auto &iParticle : particles)
            {
                iParticle->clear();
            }
        }
        else if (_gist == "particle") {
            particles.clear();
            numParticles = 0;
        }
    }
    void setParticle(Colloid* _particle)
    {
        _particle->setCharge(new ph::Charge(1, stabilization->getChargeValue(medium, _particle), _particle->getPlacement()));
        particles.push_back(_particle);        
        numParticles++;
    }
    Colloid* getParticle(unsigned long _number)
    {
        for(auto &iParticle : particles)
        {
            if (iParticle->number == _number)
            {
                return iParticle;
            }
        }
    }
};

}




#endif // CLUSTER_H
