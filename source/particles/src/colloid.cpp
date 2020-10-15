#include "colloid.h"

namespace tuco {

Colloid::Colloid(unsigned long number)
{
    this->number_ = number;
    greenKernel_ = new ph::CoulombKernal; //default
    integralSQ_ = new SymplexIntegration("quadratic");
}
Colloid::Colloid(unsigned long number, Object* object) :
    MacroParticle(number, object)
{
    greenKernel_ = new ph::CoulombKernal; //default
    integralSQ_ = new SymplexIntegration("quadratic");
}
Colloid::Colloid(unsigned long number, State* state, Object* object) :
    MacroParticle(number, state, object)
{
    greenKernel_ = new ph::CoulombKernal; //default    
    //integralSQ_ = new SymplexIntegration("quadratic");
    integralSQ_ = new SymplexIntegration("cubic");
    integralMC_ = new SymplexIntegration("quadratic");
    //integralMC_ = new MonteCarloIntegration("mc", 50000);
}
Colloid::Colloid(unsigned long _number, State* _state, Object* object, double _angle)
{
    this->number_ = _number;
    this->state_ = _state;
    object_.reset(new Object(object->getShape(), object->getMaterial()));


    greenKernel_ = new ph::CoulombKernal; //default
    //integralSQ_ = new SymplexIntegration("quadratic");
    integralSQ_ = new SymplexIntegration("cubic");
    integralMC_ = new SymplexIntegration("quadratic");
    //integralMC_ = new MonteCarloIntegration("mc", 50000);
}
Colloid::Colloid(MacroParticle* macroparticle, State* _state) :
    MacroParticle(*macroparticle)
{
    greenKernel_ = new ph::CoulombKernal; //default
    integralSQ_ = new SymplexIntegration("quadratic");
    setState(_state);
}
void Colloid::setGreenKernel(ph::GreenKernel* _greenKernel)
{
    greenKernel_ = _greenKernel;
}
void Colloid::setPhysicalModel(std::string key, PhysicalModel* physicalModel)
{
    physicalModel->setMacroParticle(this);
    physicalModelsMap_[key] = physicalModel;
}
ph::Energy Colloid::getInteractionsEnergy(MacroParticle* macroParticle, Environment* enviroment)
{
    energy_ = ph::Energy();
    if (existDipole()) {
        energy_ = ph::Energy(-dipole_->getValue()->dot(enviroment->getCreenCore()->
                                                        getDipoleOperator(getPosition(), macroParticle->getPosition()) * (*macroParticle->getDipole()->getValue())) / 2.0);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            //energy_ += ph::Energy(iElement->getChargeValue() * macroParticle->getElectricPotential(iElement->getBarycenter(), enviroment->getCreenCore()).scalar / 2.0);
            energy_ += ph::Energy(iElement->getChargeValue() * macroParticle->getElectricPotential(iElement->getBarycenter()).scalar / 2.0);
        }        
    }
    if (existSimpleCore()) {
        for (auto &iElement : *getCoreBoundaryElements())
        {
            energy_ += ph::Energy(iElement->getChargeValue() * macroParticle->getElectricPotential(iElement->getBarycenter(), enviroment->getCreenCore()).scalar / 2.0);
        }
    }
    return energy_;
}
ph::Energy Colloid::getSelfEnergy()
{
    energy_ = ph::Energy();
    if (existDipole()) {
        energy_ = ph::Energy(pow(dipole_->getValue()->norm(), 2) / (pow(getShape()->getCharacteristicSize(), 3)) / 2.0);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            energy_ += ph::Energy(iElement->getChargeValue() * getElectricPotential(iElement->getBarycenter()).scalar / 2.0);
        }
    }
    if (existSimpleCore()) {
        for (auto &iElement : *getCoreBoundaryElements())
        {
            energy_ += ph::Energy(iElement->getChargeValue() * getElectricPotential(iElement->getBarycenter()).scalar / 2.0);
        }
    }    
    return energy_;
}
ph::Energy Colloid::getExternalEnergy(ph::ElectricField* electricField)
{
    energy_ = ph::Energy();
    if (existDipole()) {
        energy_ = ph::Energy(-dipole_->getValue()->dot(electricField->getElectricStrength(getPosition()).getVector()) / 2.0);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
           energy_ += ph::Energy(iElement->getChargeValue() * electricField->getElectricPotential(iElement->getBarycenter(), getPosition()).scalar / 2.0);
        }
    }
    if (existSimpleCore()) {
        for (auto &iElement : *getCoreBoundaryElements())
        {
           energy_ += ph::Energy(iElement->getChargeValue() * electricField->getElectricPotential(iElement->getBarycenter(), getPosition()).scalar / 2.0);
        }
    }
    return energy_;
}
ph::ElectricPotential Colloid::getElectricPotential(Vector3d r)
{
    ph::ElectricPotential potential_ = ph::ElectricPotential(r);
    if (existDipole()) {
        potential_ = dipole_->getElectricPotential(r);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
/*
            if (r != iElement->getBarycenter()) {
                potential_ += ph::ElectricPotential(iElement->getChargeValue() * greenKernel_->getFunction(r, iElement->getBarycenter()), r);
            }
*/
            if (iElement->isNearestPosition(r)) {
                potential_ += ph::ElectricPotential(iElement->getChargeDensity() * integralMC_->getIntegral(&ph::GreenKernel::getFunction, greenKernel_, r, iElement), r);
            } else {
                potential_ += ph::ElectricPotential(iElement->getChargeDensity() * integralSQ_->getIntegral(&ph::GreenKernel::getFunction, greenKernel_, r, iElement), r);
            }

        }
        if(existSimpleCore())
        {
            for (auto &iElement : *getCoreBoundaryElements())
            {
/*
                if (r != iElement->getBarycenter()) {
                    potential_ += ph::ElectricPotential(iElement->getChargeValue() * greenKernel_->getFunction(r, iElement->getBarycenter()), r);
                }
*/
                if (iElement->isNearestPosition(r)) {
                    potential_ += ph::ElectricPotential(iElement->getChargeDensity() * integralMC_->getIntegral(&ph::GreenKernel::getFunction, greenKernel_, r, iElement), r);
                } else {
                    potential_ += ph::ElectricPotential(iElement->getChargeDensity() * integralSQ_->getIntegral(&ph::GreenKernel::getFunction, greenKernel_, r, iElement), r);
                }
            }
        }
    }
    return potential_;
}
ph::ElectricPotential Colloid::getElectricPotential(Vector3d r, ph::GreenKernel* _kernel)
{
    ph::ElectricPotential potential_ = ph::ElectricPotential(r);
    if (existDipole()) {
        potential_ = dipole_->getElectricPotential(r, _kernel);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            if (r != iElement->getBarycenter()) {
                potential_ += ph::ElectricPotential(iElement->getChargeValue() * _kernel->getFunction(r, iElement->getBarycenter()), r);
            }
        }
        if(existSimpleCore())
        {
            for (auto &iElement : *getCoreBoundaryElements())
            {
                if (r != iElement->getBarycenter()) {
                    potential_ += ph::ElectricPotential(iElement->getChargeValue() * _kernel->getFunction(r, iElement->getBarycenter()), r);
                }
            }
        }
    }
    return potential_;
}
ph::ElectricStrength Colloid::getElectricStrength(Vector3d r)
{
    ph::ElectricStrength strength_ = ph::ElectricStrength(r);
    if (existDipole()) {
        strength_ += dipole_->getElectricStrength(r);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            if (r != iElement->getBarycenter()) {
                strength_  += ph::ElectricStrength(iElement->getChargeValue() * greenKernel_->getGradient(r, iElement->getBarycenter()), r);
            }
        }
        if(existSimpleCore())
        {
            for (auto &iElement : *getCoreBoundaryElements())
            {
                if (r != iElement->getBarycenter()) {
                    strength_  += ph::ElectricStrength(iElement->getChargeValue() * greenKernel_->getGradient(r, iElement->getBarycenter()), r);
                }
            }
        }
    }
    return strength_;
}
ph::ElectricStrength Colloid::getElectricStrength(Vector3d r, ph::GreenKernel* _kernel)
{
    ph::ElectricStrength strength_ = ph::ElectricStrength(r);
    if (existDipole()) {
        strength_ += dipole_->getElectricStrength(r, _kernel);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            strength_  += ph::ElectricStrength(iElement->getChargeValue() * _kernel->getGradient(r, iElement->getBarycenter()), r);
        }
        if(existSimpleCore())
        {
            for (auto &iElement : *getCoreBoundaryElements())
            {
                strength_  += ph::ElectricStrength(iElement->getChargeValue() * _kernel->getGradient(r, iElement->getBarycenter()), r);
            }
        }
    }
    return strength_;
}

}
