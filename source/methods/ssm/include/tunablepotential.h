#ifndef TUNABLEPOTENTIAL_H
#define TUNABLEPOTENTIAL_H

#include "state.h"
#include "energy.h"

namespace tuco {


struct TunablePotential
{
    TunablePotential()
    {

    }
    void setPotentialState(double _trn, ph::Energy energy)
    {
        potentialMap_[_trn] = energy;
    }
    void record(std::string _address, std::string _name)
    {
        std::string fullAddress = _address + _name + ".tp"; // TunableParticleFormat
        std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
        for (auto& iConfiguration : potentialMap_)
        {
            out << iConfiguration.first
                << "  "
                << iConfiguration.second.getValue()
                << "\n";
        }
        out.close();
    }
private:
    std::map<double, ph::Energy> potentialMap_;
};

}

#endif // TUNABLEPOTENTIAL_H
