#include "cscolloid.h"

namespace tuco {

CSColloid::CSColloid(unsigned long number)
{
    this->number_ = number;
    greenKernel_ = new ph::CoulombKernal; //default
}
CSColloid::CSColloid(unsigned long number, Object* object) :
    MacroParticle(number, object)
{
    greenKernel_ = new ph::CoulombKernal; //default
}
CSColloid::CSColloid(unsigned long number, State* state, Object* object) :
    MacroParticle(number, state, object)
{
    greenKernel_ = new ph::CoulombKernal; //default
}
CSColloid::CSColloid(MacroParticle* macroparticle, State* _state) :
    MacroParticle(*macroparticle)
{
    greenKernel_ = new ph::CoulombKernal; //default
    setState(_state);
}
void CSColloid::setGreenKernel(ph::GreenKernel* _greenKernel)
{
    greenKernel_ = _greenKernel;
}
void CSColloid::setPhysicalModel(std::string key, PhysicalModel* physicalModel)
{
    physicalModel->setMacroParticle(this);
    physicalModelsMap_[key] = physicalModel;
}
ph::Energy CSColloid::getInteractionsEnergy(MacroParticle* macroParticle, Environment* enviroment)
{
    energy_ = ph::Energy();
    if (existDipole()) {
        energy_ = ph::Energy(-dipole_->getValue()->dot(enviroment->getCreenCore()->
                                                        getDipoleOperator(getPosition(), macroParticle->getPosition()) * (*macroParticle->getDipole()->getValue())) / 2.0);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            energy_ += ph::Energy(iElement->getChargeValue() * macroParticle->getElectricPotential(iElement->getBarycenter(), enviroment->getCreenCore()).scalar / 2.0);
        }
    }
    return energy_;
}
ph::Energy CSColloid::getSelfEnergy()
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
    return energy_;
}
ph::Energy CSColloid::getExternalEnergy(ph::ElectricField* electricField)
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
    return energy_;
}
ph::ElectricPotential CSColloid::getElectricPotential(Vector3d r)
{
    ph::ElectricPotential potential_ = ph::ElectricPotential(r);
    if (existDipole()) {
        potential_ = dipole_->getElectricPotential(r);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            if (r != iElement->getBarycenter()) {
                potential_ += ph::ElectricPotential(iElement->getChargeValue() * greenKernel_->getFunction(r, iElement->getBarycenter()) / 2.0, r);
            }
        }
    }
    return potential_;
}
ph::ElectricPotential CSColloid::getElectricPotential(Vector3d r, ph::GreenKernel* _kernel)
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
    }
    return potential_;
}
ph::ElectricStrength CSColloid::getElectricStrength(Vector3d r)
{
    ph::ElectricStrength strength_ = ph::ElectricStrength(r);
    if (existDipole()) {
        strength_ += dipole_->getElectricStrength(r);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            if (r != iElement->getBarycenter()) {
                strength_  += ph::ElectricStrength(iElement->getChargeValue() * greenKernel_->getGradient(r, iElement->getBarycenter()) / 2.0, r);
            }
        }
    }
    return strength_;
}
ph::ElectricStrength CSColloid::getElectricStrength(Vector3d r, ph::GreenKernel* _kernel)
{
    ph::ElectricStrength strength_ = ph::ElectricStrength(r);
    if (existDipole()) {
        strength_ += dipole_->getElectricStrength(r, _kernel);
    }
    if (existPhysicalMesh()) {
        for (auto &iElement : *getBoundaryElements())
        {
            strength_  += ph::ElectricStrength(iElement->getChargeValue() * _kernel->getGradient(r, iElement->getBarycenter()) / 2.0, r);
        }
    }
    return strength_;
}

}
