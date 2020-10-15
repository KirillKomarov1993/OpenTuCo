#ifndef CLUSTERENERGYMETHOD_H
#define CLUSTERENERGYMETHOD_H

#include "energyelementmethod.h"
#include "tunablecluster.h"
#include "surfaceenergyequation.h"

namespace tuco {

class ClusterEnergyMethod : public EnergyElementMethod
{
    Matrix3d P_;
    ph::Energy energy_;
    ph::CoulombKernal* greenKernel;
    std::shared_ptr<TunableCluster> cluster;
//**Basic methods and functions:
    inline void* setNullDensityBlock(unsigned short _p, unsigned short _q, MacroParticle* _macroParticle1, MacroParticle* _macroParticle2)
    {
        for (auto &iElement1 : *_macroParticle1->getBoundaryElements())
        {
            p_ =  static_cast<unsigned short>(iElement1->getNumber() - 1) + _p;
            for (auto &iElement2 : *_macroParticle2->getBoundaryElements())
            {
                q_ = static_cast<unsigned short>(iElement2->getNumber() - 1) + _q;
                nullDensityMatrix->setElement(p_, q_, (ph::getKronProduct(iElement1->getNormal(), iElement2->getNormal()) * P_).trace() / 2.0);
            }
        }
    }
    inline void* setDashDensityBlock(unsigned short _p, unsigned short _q, MacroParticle* _macroParticle1, MacroParticle* _macroParticle2)
    {
        for (auto &iElement1 : *_macroParticle1->getBoundaryElements())
        {
            p_ =  static_cast<unsigned short>(iElement1->getNumber() - 1) + _p;
            for (auto &iElement2 : *_macroParticle2->getBoundaryElements())
            {
                q_ = static_cast<unsigned short>(iElement2->getNumber() - 1) + _q;
                dashDensityMatrix->setElement(p_, q_, (ph::getKronProduct(iElement1->getNormal(), iElement2->getNormal()) * P_).trace() / 2.0 * unknowns(p_));
            }
        }
    }
    void computerDensityMatrix(std::function<void*(EnergyElementMethod*, unsigned short, unsigned short, MacroParticle*, MacroParticle*)> _function)
    {
        P_ << 1, 0, 0,
              0, 1, 0,
              0, 0, 0;
        unsigned short p, q;
    //**Заполнение матрицы:
        p = 0;
        for (auto& iParticle1 : *cluster->getMacroParticleMap())
        {
            std::cout << "Number of particle n1: " << iParticle1.second->getNumber() << std::endl;
            q = 0;
            for (auto& iParticle2 : *cluster->getMacroParticleMap())
            {
                std::cout << "          Number of particle n2: " << iParticle2.second->getNumber() << std::endl;
                _function(this, p, q, iParticle1.second, iParticle2.second);
                q += coef * iParticle2.second->getElementCount();
            }
            p += coef * iParticle1.second->getElementCount();
        }
        //nullDensityMatrix->record();
        //std::cin.get();
    }
    inline ph::Energy setEnegyBlock(unsigned short p, unsigned short q, VectorXd& _value, MacroParticle* _particle1, MacroParticle* _particle2);
//**Реализация виртуальных методов и функций:
    void setElementEnergis();
    void setColumnVector(ph::ElectricField* _field);
public:
    ClusterEnergyMethod(TunableCluster* _system, Integration* _integralSQ, Integration* _integralMC);
//**Реализация виртуальных методов и функций:
    void setInteractionsMatrix();    
};

}

#endif // CLUSTERENERGYMETHOD_H
