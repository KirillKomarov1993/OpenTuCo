#ifndef PERTURBATIONDIPOLEMETHOD_H
#define PERTURBATIONDIPOLEMETHOD_H

#include "mathlist.h"
#include "dipolemodel.h"
#include "dipole.h"
#include "homogemiusfield.h"
#include "tucomethod.h"



#include "integralequation.h"
#include "tunablecluster.h"

namespace tuco {

struct Formula
{
    Formula(std::string _note) :
        note(_note)
    {

    }
    std::string getNote()
    {
        return note;
    }
private:
    std::string note;
};

struct EnergyDiagrams
{
    EnergyDiagrams(TunableCluster* _cluster, ph::ElectricField* _field)
    {
        matrix = new DensityMatrix(3);
    }
    ph::Energy getDiagram(Formula* formula)
    {
        return ph::Energy();
    }
private:
    DensityMatrix* matrix;
};


class PerturbationDipoleMethod: public TuCoMethod
{
public:
    PerturbationDipoleMethod();
    virtual ~ PerturbationDipoleMethod();
//**Реализация виртуальных методов:
    void setBlock(MacroParticle* _particle1, MacroParticle* _particle2);
    void computer(ph::ElectricField* _field);
//**Абсолютно виртуальные методы и функции:
    virtual void setDipoleMoment(VectorXd _p) = 0;
    virtual void setInteractionsMatrix() = 0;
    virtual VectorXd getColumnVector(ph::ElectricStrength electricStrength) = 0;
    virtual VectorXd getColumnVector(ph::ElectricField* electricStrength) = 0;
};

class ClusterPerturbationMethod: public PerturbationDipoleMethod
{
    TunableCluster* cluster;
public:
    ClusterPerturbationMethod(TunableCluster* _cluster) :
        cluster(_cluster)
    {

    }
    void computer(ph::ElectricField* _field)
    {
        for (auto&& iParticle : *cluster->getMacroParticleMap())
        {
            iParticle.second->setDipole(getPerturbationDipole(iParticle, _field));
        }
    }
};

}



class FullPerturbationMethod : private PerturbationDipoleMethod
{
    double cos_phi12_, cos_phi23_, cos_phi13_, cos_phi14_, cos_phi24_, cos_phi34_;
    double r12_norm_, r12in3_, r13_norm_, r13in3_, r23_norm_, r23in3_;
    double r1_norm_, r1in3_, r2_norm_, r2in3_, r3_norm_, r3in3_, r4_norm_, r4in3_;
    double chi_, amplitude_;
    double fieldAmplitude_;
public:
    int order;
    FullPerturbationMethod(int _order, Cluster* _system) :
        order(_order), PerturbationDipoleMethod(_system)
    {

    }
    double getMeanAmplitude()
    {
        return 1.0;
    }
    double getMeanAmplitude(Vector _r1, Vector _r2)
    {
        cos_phi12_ = _r1.dot(_r2) / (_r1.norm() * _r2.norm());
        return -(4.0 - 9.0 * cos_phi12_ * cos_phi12_);
    }
    double getMeanAmplitude(Vector _r1, Vector _r2, Vector _r3)
    {
        cos_phi12_ = _r1.dot(_r2) / (_r1.norm() * _r2.norm());
        cos_phi23_ = _r2.dot(_r3) / (_r2.norm() * _r3.norm());
        cos_phi13_ = _r1.dot(_r3) / (_r1.norm() * _r3.norm());
        return (7.0 - 9.0 * (cos_phi12_ * cos_phi12_ + cos_phi23_ * cos_phi23_ + cos_phi13_ * cos_phi13_) + 27.0 * cos_phi12_ * cos_phi23_ * cos_phi13_);
    }
    double getMeanAmplitude(Vector _r1, Vector _r2, Vector _r3, Vector _r4)
    {
        cos_phi12_ = _r1.dot(_r2) / (_r1.norm() * _r2.norm());
        cos_phi23_ = _r2.dot(_r3) / (_r2.norm() * _r3.norm());
        cos_phi13_ = _r1.dot(_r3) / (_r1.norm() * _r3.norm());
        cos_phi14_ = _r1.dot(_r4) / (_r1.norm() * _r4.norm());
        cos_phi24_ = _r2.dot(_r4) / (_r2.norm() * _r4.norm());
        cos_phi34_ = _r3.dot(_r4) / (_r3.norm() * _r4.norm());
        return -(10.0 - 9.0 * (cos_phi12_ * cos_phi12_ + cos_phi23_ * cos_phi23_ + cos_phi24_ * cos_phi24_ + cos_phi14_ * cos_phi14_)
                 + 27.0 * (cos_phi12_ * cos_phi23_ * cos_phi13_ + cos_phi12_ * cos_phi24_ * cos_phi14_ + cos_phi13_ * cos_phi34_ * cos_phi14_ + cos_phi23_ * cos_phi34_ * cos_phi14_)
                 - 81.0 * cos_phi12_ * cos_phi23_ * cos_phi34_ * cos_phi14_);
    }
    double getFunction(Vector _r1)
    {
        r1_norm_ = _r1.norm();  r1in3_ = (r1_norm_* r1_norm_ * r1_norm_);
        if (r1_norm_ != 0.0) {
            return getMeanAmplitude() / (r1in3_);
        }
        else {
            return 0.0;
        }
    }
    double getFunction(Vector _r1, Vector _r2)
    {
        r1_norm_ = _r1.norm();  r1in3_ = (r1_norm_* r1_norm_ * r1_norm_);
        r2_norm_ = _r2.norm();  r2in3_ = (r2_norm_* r2_norm_ * r2_norm_);
        if (r1_norm_ * r2_norm_ != 0.0) {
            return getMeanAmplitude(_r1, _r2) / (r1in3_ * r2in3_);
        }
        else {
            return 0.0;
        }
    }
    double getFunction(Vector _r1, Vector _r2, Vector _r3)
    {
        r1_norm_ = _r1.norm();  r1in3_ = (r1_norm_* r1_norm_ * r1_norm_);
        r2_norm_ = _r2.norm();  r2in3_ = (r2_norm_* r2_norm_ * r2_norm_);
        r3_norm_ = _r3.norm();  r3in3_ = (r3_norm_* r3_norm_ * r3_norm_);
        if (r1_norm_ * r2_norm_ * r3_norm_ != 0.0) {
            return getMeanAmplitude(_r1, _r2, _r3) / (r1in3_ * r2in3_ * r3in3_);
        }
        else {
            return 0.0;
        }
    }
    double getFunction(Vector _r1, Vector _r2, Vector _r3, Vector _r4)
    {
        r1_norm_ = _r1.norm();  r1in3_ = (r1_norm_* r1_norm_ * r1_norm_);
        r2_norm_ = _r2.norm();  r2in3_ = (r2_norm_* r2_norm_ * r2_norm_);
        r3_norm_ = _r3.norm();  r3in3_ = (r3_norm_* r3_norm_ * r3_norm_);
        r4_norm_ = _r4.norm();  r4in3_ = (r4_norm_* r4_norm_ * r4_norm_);
        if (r1_norm_ * r2_norm_ * r3_norm_ * r4_norm_ != 0.0) {
            return getMeanAmplitude(_r1, _r2, _r3, _r4) / (r1in3_ * r2in3_ * r3in3_ * r4in3_);
        }
        else {
            return 0.0;
        }
    }
    Energy* getSelfEnergy(Particle* _particle1, Particle* _particle2)
    {
        lambda = chi_ / pow(2.0 * _particle1->object->shape->radius, 3);
        Energy* energy = new Energy(0.0, "electric");
        if (order >= 1) {
            energy->setEnergy(amplitude_ * 16.0 * lambda * getFunction(_particle1->getPlacement() - _particle2->getPlacement()));
        }
        if (order >= 2) {
            for (auto &iParticle1 : cluster->particles)
            {
                 energy->addEnergy(amplitude_ *  8.0 * lambda * chi_ *
                                        (
                                            getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                        _particle1->getPlacement() - iParticle1->getPlacement()) +
                                            getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                        _particle2->getPlacement() - iParticle1->getPlacement())
                                        )
                                  );
            }
        }
        if (order >= 3) {
            for (auto &iParticle1 : cluster->particles)
            {
                for (auto &iParticle2 : cluster->particles)
                {
                    energy->addEnergy(amplitude_ *  16.0 * lambda * chi_ * chi_ *
                                            (
                                                getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                            _particle1->getPlacement() - iParticle1->getPlacement(),
                                                            iParticle1->getPlacement() - iParticle2->getPlacement()) +
                                                getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                            _particle2->getPlacement() - iParticle1->getPlacement(),
                                                            iParticle1->getPlacement() - iParticle2->getPlacement())
                                            )
                                     );
                }
            }
        }
        return energy;
    }
    Energy* getExternalEnergy(Particle* _particle1, Particle* _particle2)
    {
        Energy* energy = new Energy(0.0, "electric");
        if (order >= 0) {
            energy->setEnergy(-amplitude_ * getFunction(_particle1->getPlacement() - _particle2->getPlacement()));
        }
        if (order >= 1) {
            for (auto &iParticle1 : cluster->particles)
            {
                 energy->addEnergy(-amplitude_ * chi_ *
                                        (
                                            getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                        _particle2->getPlacement() - iParticle1->getPlacement())
                                        )
                                  );
            }
        }
        if (order >= 2) {
            for (auto &iParticle1 : cluster->particles)
            {
                for (auto &iParticle2 : cluster->particles)
                {
                    energy->addEnergy(-amplitude_ * chi_ * chi_ *
                                            (
                                                getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                            _particle2->getPlacement() - iParticle1->getPlacement(),
                                                            iParticle1->getPlacement() - iParticle2->getPlacement())
                                            )
                                     );
                }
            }
        }
        if (order >= 3) {
            for (auto &iParticle1 : cluster->particles)
            {
                for (auto &iParticle2 : cluster->particles)
                {
                    for (auto &iParticle3 : cluster->particles)
                    {
                        energy->addEnergy(-amplitude_ * chi_ * chi_ * chi_ *
                                                (
                                                    getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                                _particle2->getPlacement() - iParticle1->getPlacement(),
                                                                iParticle1->getPlacement() - iParticle2->getPlacement(),
                                                                iParticle2->getPlacement() - iParticle3->getPlacement())
                                                )
                                        );
                    }
                }
            }
        }
        return energy;
    }
    Energy* getElectrostaticEnergy(Particle* _particle1, Particle* _particle2)
    {
        return new Energy(-amplitude_ * getFunction(_particle1->getPlacement() - _particle2->getPlacement()), "electric");
    }
    Energy* getDebyeEnergy(Particle* _particle1, Particle* _particle2)
    {
        Energy* energy = new Energy(0.0, "electric");
        if (order >= 1) {
            for (auto &iParticle1 : cluster->particles)
            {
                 energy->addEnergy(-amplitude_ * chi_ *
                                        (
                                            getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                        _particle2->getPlacement() - iParticle1->getPlacement()) +
                                            getFunction(_particle1->getPlacement() - iParticle1->getPlacement(),
                                                        _particle1->getPlacement() - _particle2->getPlacement())
                                        )
                                  );
            }
        }
        if (order >= 2) {
            for (auto &iParticle1 : cluster->particles)
            {
                for (auto &iParticle2 : cluster->particles)
                {
                    energy->addEnergy(-amplitude_ * chi_ * chi_ *
                                         (
                                             getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                         _particle2->getPlacement() - iParticle1->getPlacement(),
                                                         iParticle1->getPlacement() - iParticle2->getPlacement()) +
                                             getFunction(_particle1->getPlacement() - iParticle1->getPlacement(),
                                                         iParticle1->getPlacement() - iParticle2->getPlacement(),
                                                         _particle1->getPlacement() - _particle2->getPlacement())
                                         )
                                     );
                }
            }
        }
        if (order >= 3) {
            for (auto &iParticle1 : cluster->particles)
            {
                for (auto &iParticle2 : cluster->particles)
                {
                    for (auto &iParticle3 : cluster->particles)
                    {
                        energy->addEnergy(-amplitude_ * chi_ * chi_ * chi_ *
                                             (
                                                 getFunction(_particle1->getPlacement() - _particle2->getPlacement(),
                                                             _particle2->getPlacement() - iParticle1->getPlacement(),
                                                             iParticle1->getPlacement() - iParticle2->getPlacement(),
                                                             iParticle2->getPlacement() - iParticle3->getPlacement()) +
                                                 getFunction(_particle1->getPlacement() - iParticle1->getPlacement(),
                                                             iParticle1->getPlacement() - iParticle2->getPlacement(),
                                                             iParticle2->getPlacement() - iParticle3->getPlacement(),
                                                             _particle1->getPlacement() - _particle2->getPlacement())
                                             )
                                         );
                    }
                }
            }
        }
        return energy;
    }
    Energy* getLondonEnergy(Particle* _particle1, Particle* _particle2)
    {
        Energy* energy = new Energy(0.0, "electric");
        if (order >= 2) {
            for (auto &iParticle1 : cluster->particles)
            {
                for (auto &iParticle2 : cluster->particles)
                {
                    energy->addEnergy(-amplitude_ * chi_ * chi_ * getFunction(_particle1->getPlacement() - iParticle1->getPlacement(),
                                                                              _particle1->getPlacement() - _particle2->getPlacement(),
                                                                              _particle2->getPlacement() - iParticle2->getPlacement())
                                      );
                }
            }
        }
        if (order >= 3) {
            for (auto &iParticle1 : cluster->particles)
            {
                for (auto &iParticle2 : cluster->particles)
                {
                    for (auto &iParticle3 : cluster->particles)
                    {
                        energy->addEnergy(-amplitude_ * chi_ * chi_ * chi_ *
                                             (
                                                 getFunction(_particle1->getPlacement() - iParticle1->getPlacement(),
                                                             iParticle1->getPlacement() - iParticle2->getPlacement(),
                                                             _particle1->getPlacement() - _particle2->getPlacement(),
                                                             _particle2->getPlacement() - iParticle3->getPlacement()) +
                                                 getFunction(_particle1->getPlacement() - iParticle1->getPlacement(),
                                                             _particle1->getPlacement() - _particle2->getPlacement(),
                                                             _particle2->getPlacement() - iParticle2->getPlacement(),
                                                             iParticle2->getPlacement() - iParticle3->getPlacement())
                                             )
                                         );
                    }
                }
            }
        }
        return energy;
    }
    void setInteractions()
    {
        for (auto &iParticle1 : cluster->particles)
        {
            Bond* bond  = new Bond(iParticle1->getNumber());
            Energy* energy = new Energy(0.0, "electric");
            for (auto &iParticle2 : cluster->particles)
            {
               if (iParticle1->number != iParticle2->number)
               {
                   chi_ = (*iParticle1->object->volume) * 3.0 / (4.0 * math::pi()) * (iParticle1->getMaterial()->epsilon / cluster->getMediumMaterial()->epsilon - 1)
                                                                              / (iParticle1->getMaterial()->epsilon / cluster->getMediumMaterial()->epsilon + 2);
                   amplitude_ = pow(chi_ * fieldAmplitude_, 2) / 4.0;
                   bond->setEnergy("self-energy", *getSelfEnergy(iParticle1, iParticle2));
                   bond->setEnergy("external-energy", *getExternalEnergy(iParticle1, iParticle2));
                   energy->energy += getElectrostaticEnergy(iParticle1, iParticle2)->energy + getDebyeEnergy(iParticle1, iParticle2)->energy + getLondonEnergy(iParticle1, iParticle2)->energy;
               }
            }
            bond->setEnergy("induced-energy", *energy);
            iParticle1->setBond(bond);
        }
    }
    void computer(double _fieldMagnitude)
    {
        fieldAmplitude_ = _fieldMagnitude;
        setInteractions();
    }
};


#endif // PERTURBATIONDIPOLEMETHOD_H
