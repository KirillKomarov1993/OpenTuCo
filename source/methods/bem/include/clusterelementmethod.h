#ifndef CLUSTERELEMENTMETHOD_H
#define CLUSTERELEMENTMETHOD_H

#include "boundaryelementmethod.h"
#include "tunablecluster.h"

namespace tuco {

class ClusterElementMethod : public BoundaryElementMethod
{
    double beta;
    double shellClausius;
    double coreClausius;
    double shellPolariazation;
    double corePolariazation;
    std::string type_;
    VectorXd sigma;
    std::shared_ptr<TunableCluster> cluster;
//**Реализация виртуальных методов и функций:
    void setSurfaceMultipoles(VectorXd _value);
    void setColumnVector(ph::ElectricField* _field);
public:
    ClusterElementMethod(TunableCluster* _system, IntegralEquation* _equation);    
    ClusterElementMethod(std::string _type, TunableCluster* _system, IntegralEquation* _equation);
    ClusterElementMethod(std::string _type, TunableCluster* _system, IntegralEquation* _shellEquation, IntegralEquation* _coreEquation);
//**Реализация виртуальных методов и функций:
    void setInteractionsMatrix();    
    void setStabilizingBlock(int _p, int _q, MacroParticle* _particle)
    {
        int p_, q_;
        for (auto &iElement1 : *_particle->getBoundaryElements())
        {
            p_ =  (iElement1->getNumber() - 1) + _p;
            for (auto &iElement2 : *_particle->getBoundaryElements())
            {
                q_ =  (iElement2->getNumber() - 1) + _q;
                delta(p_, q_) = iElement1->getArea() / iElement2->getArea() * (ph::kronecker(p_,q_) - 1);
            }
        }
    }
};

}

#endif // CLUSTERELEMENTMETHOD_H
