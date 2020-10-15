/************************************************
 * Module: MacroParticle.h
 * Author: Kirill A. Komarov
 * Modified: 20 Jan 2019 /
 * Purpose: Declaration of the class MacroParticle
*************************************************/

#ifndef MACROPARTICLE_H
#define MACROPARTICLE_H

#include <memory>

#include "particle.h"
#include "state.h"
#include "energy.h"
#include "electricstrength.h"
#include "medium.h"
#include "hamiltanian.h"
#include "corelinker.h"
#include "quadrupole.h"

namespace tuco {

//**Здесь задается макрочастица с помощью паттерна "псевдо-Декоратор":
//  В реализации настоящего класса отсутствует функция getObject(),
//  таким образом класс является оберткой класса Object, причем работать
//  можно, как с базовым классом, так и обернутым.
struct MacroParticle : public cs::Particle,
                       public PhysicalMesh
{
    MacroParticle();
    MacroParticle(unsigned long number, Object* object);
    MacroParticle(unsigned long number, State* state, Object* object);
    virtual ~MacroParticle();
//**Псевдо-обернутые функции класса <<Object>>:
    double getMass();
    double getVolume();
    Shape* getShape();
    Material* getMaterial();    
//**Обертка объекта <<PhysicalMesh>> (здесь, чистый "Декоратор"):
    void record(std::string _address, std::string _name)
    {
        physicalMesh_->record(_address, _name + "_shell");
        if (existSimpleCore()) {
            corelinkers_.back()->getPhysicalMesh()->record(_address, _name + "_core");
        }
    }
    unsigned short getElementCount();
    std::vector<BoundaryElement*>* getBoundaryElements();
//**Базовые функции этого класса:    
    void setPhysicalMesh(PhysicalMesh* _physicalMesh);
    void setState(State* _state);
    void setCoreLinker(CoreLinker* core)
    {
        //core->getPhysicalMesh()->setBoundaryElements(core->getObject()->getShape(), getState());
        corelinkers_.push_back(core);
        if (core->isSimplyCore()) {
            corelinkers_.back()->getPhysicalMesh()->setBoundaryElements(core->getObject()->getShape(), getState());
            simpleCoreFlag_ = true;
        }
        if (core->isNanoInclusionCore()) {

        }

    }
    Vector3d getPosition();
    State* getState()
    {
        return state_;
    }
    ph::Dipole* getDipole();
    ph::Quadrupole* getQuadrupole()
    {
        /*
        if (dipoleFlag_) {
            return dipole_.get();
        }
        */
        if (existPhysicalMesh()) {

            Matrix3d Q = Matrix3d::Zero();
            for (auto &iElement : *getBoundaryElements())
            {
                Q += (3.0 * ph::getKronProduct(iElement->getBarycenter(), iElement->getBarycenter())
                          - iElement->getBarycenter().dot(iElement->getBarycenter()) * Matrix3d::Identity()) * iElement->getChargeValue();
            }
            if (existSimpleCore()) {
                for (auto &iElement : *getCoreBoundaryElements())
                {
                    Q += (3.0 * ph::getKronProduct(iElement->getBarycenter(), iElement->getBarycenter())
                              - iElement->getBarycenter().dot(iElement->getBarycenter()) * Matrix3d::Identity()) * iElement->getChargeValue();
                }
            }
            quadrupole_.reset(new ph::Quadrupole(1, Q, getPosition()));
            return quadrupole_.get();
        }
    }
  //Расчет энергии частицы:
    Hamiltonian* getHamiltanian();    
    PhysicalModel* getPhysicalModel(std::string _key);
    std::map<std::string, PhysicalModel*>* getPhysicalModelMap();
//**Виртуальыне функции:
    virtual void setDipole(ph::Dipole* dipole);
    virtual void setPhysicalModel(std::string key, PhysicalModel* physicalModel);
//**Абсолютно виртуальные функции:    
    virtual ph::Energy getInteractionsEnergy(MacroParticle* macroParticle,Environment* enviroment) = 0;
    virtual ph::Energy getSelfEnergy() = 0;
    virtual ph::Energy getExternalEnergy(ph::ElectricField* electricField) = 0;
    virtual ph::ElectricPotential getElectricPotential(Vector3d r) = 0;
    virtual ph::ElectricPotential getElectricPotential(Vector3d r, ph::GreenKernel*) = 0;
    virtual ph::ElectricStrength getElectricStrength(Vector3d r) = 0;
    virtual ph::ElectricStrength getElectricStrength(Vector3d r, ph::GreenKernel*) = 0;
//**New function for Colloid and CSColloid:
    unsigned long getCoreElementCount()
    {
        if(!corelinkers_.empty()) {
            return corelinkers_.back()->getPhysicalMesh()->getBoundaryElements()->size();
        }
    }
    Material* getCoreMaterial()
    {
        return corelinkers_.back()->getObject()->getMaterial();
    }
    Shape* getCoreShape()
    {
        return corelinkers_.back()->getObject()->getShape();
    }
    std::vector<BoundaryElement*>* getCoreBoundaryElements()
    {
        return corelinkers_.back()->getPhysicalMesh()->getBoundaryElements();
    }
    virtual PhysicalMesh* getPhysicalMesh() = 0;
//**New function for Colloid with Nano-Inclusions:
    NanoInclusionCore* getNanoInclusionCore()
    {
        return corelinkers_.back()->getNanoInclusionCore();
    }
    CoreLinker* getCoreLinker()
    {
        return corelinkers_.back();
    }
//**Базовые защищенные функции:
    bool existDipole()
    {
        return  dipoleFlag_;
    }
    bool existPhysicalMesh()
    {
        return  physMeshFlag_;
    }
    bool existSimpleCore()
    {
        return simpleCoreFlag_;
    }
    bool existNanoInclusionCore()
    {
        return coreNIFlag_;
    }
protected:
    State* state_;
    std::shared_ptr<ph::Dipole> dipole_;
    std::shared_ptr<ph::Quadrupole> quadrupole_;
    std::shared_ptr<Hamiltonian> hamiltanian_;
    std::shared_ptr<PhysicalMesh> physicalMesh_;   
    std::shared_ptr<Object> object_; // Geometry + Material
    std::shared_ptr<cs::Particle> particle_; // Наследник от Partcle содержащейся в узле (у нее есть number и id)
//**Контейнеры:
    std::map<std::string, PhysicalModel*> physicalModelsMap_;
private:
    bool simpleCoreFlag_ = false;
    bool coreNIFlag_ = false;
    bool dipoleFlag_ = false;
    bool physMeshFlag_ = false;
//**Закрытая базовая функция:
    State* getState_();
//**Закрытая функция-обертка объекта <<PhysicalObject>>:
    void setBoundaryElements(Shape* _shape, State* _state);
//**Объекты для ядра композитной частицы:
    std::vector<CoreLinker*> corelinkers_;
};

}

#endif // MACROPARTICLE_H
