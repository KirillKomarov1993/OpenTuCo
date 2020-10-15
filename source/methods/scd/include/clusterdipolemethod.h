#ifndef CLUSTERDIPOLEMETHOD_H
#define CLUSTERDIPOLEMETHOD_H

#include "selfconsistentmethod.h"
#include "tunablecluster.h"
#include "dipole.h"

namespace tuco {

class ClusterDipoleMethod : public SelfConsistentMethod
{
    TunableCluster* cluster;
public:    
    ClusterDipoleMethod(TunableCluster* _cluster, DipoleModel* _model);
//**Реализация виртуальных методов и функций:
    void setDipoleMoment(VectorXd _p);
    void setInteractionsMatrix();
    VectorXd getColumnVector(ph::ElectricStrength electricStrength)
    {

    }
    VectorXd getColumnVector(ph::ElectricField* electricStrength);

};

}

#endif // CLUSTERDIPOLEMETHOD_H
