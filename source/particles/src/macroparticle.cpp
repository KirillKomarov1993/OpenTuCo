#include "macroparticle.h"

namespace tuco {

MacroParticle::MacroParticle() :
    hamiltanian_(new Hamiltonian)
{

}
MacroParticle::MacroParticle(unsigned long number, Object* object) :
    hamiltanian_(new Hamiltonian), object_(object)
{
    this->number_ = number;
}
MacroParticle::MacroParticle(unsigned long number, State* _state, Object* object) :
    state_(_state),hamiltanian_(new Hamiltonian), object_(object)
{
    this->number_ = number;
}
MacroParticle::~MacroParticle()
{

}
// Обернутые функции класса <<Object>>:
double MacroParticle::getMass()
{
    return object_->getMass();
}
double MacroParticle::getVolume()
{
    return object_->getVolume();
}
Material* MacroParticle::getMaterial()
{
    return object_->getMaterial();
}
Shape* MacroParticle::getShape()
{
    return object_->getShape();
}
//**Обертка объекта <<ElectroObject>> (здесь, чистый "Декоратор"):
unsigned short MacroParticle::getElementCount()
{
    return physicalMesh_->getElementCount();
}
std::vector<BoundaryElement*>* MacroParticle::getBoundaryElements()
{
    return physicalMesh_->getBoundaryElements();
}
//**Базовые функции этого класса:
void MacroParticle::setPhysicalMesh(PhysicalMesh* _physicalMesh)
{
    this->physicalMesh_.reset(_physicalMesh);
    setBoundaryElements(getShape(), getState_());
}
void MacroParticle::setState(State* _state)
{
    this->state_->setPosition(_state->getPosition());
/*
    this->state_ = _state;    
    if (existPhysicalMesh()) {
        this->physicalMesh_->setBoundaryElements(getShape(), getState_());
    }
*/
}
Vector3d MacroParticle::getPosition()
{
    return state_->getPosition();
}
ph::Dipole* MacroParticle::getDipole()
{
    if (dipoleFlag_) {
        return dipole_.get();
    }
    if (existPhysicalMesh()) {
        Vector3d p(0.0, 0.0, 0.0);
        /*
        for (auto &iElement : *getBoundaryElements())
        {
            p += iElement->getBarycenter() * iElement->getChargeValue();
        }
        */
        if (existSimpleCore()) {
            for (auto &iElement : *getCoreBoundaryElements())
            {
                p += iElement->getBarycenter() * iElement->getChargeValue();
            }
        }
        std::cout << p.norm() << std::endl;
        std::cin.get();
        return new ph::Dipole(1, p, getPosition());
    }
}
void MacroParticle::setDipole(ph::Dipole* dipole)
{
    dipole->setPosition(state_->getPosition());
    dipole_.reset(dipole);
    dipoleFlag_ = true;
}
//Расчет энергии частицы:
Hamiltonian* MacroParticle::getHamiltanian()
{
    return hamiltanian_.get();
}
void MacroParticle::setPhysicalModel(std::string key, PhysicalModel* physicalModel)
{
    physicalModelsMap_[key] = physicalModel;
}
PhysicalModel* MacroParticle::getPhysicalModel(std::string _key)
{
    if (physicalModelsMap_.count(_key)) {
        return physicalModelsMap_[_key];
    }
    return NULL;
}
std::map<std::string, PhysicalModel*>* MacroParticle::getPhysicalModelMap()
{
    return &physicalModelsMap_;
}

//**Закрытая функция-обертка объекта <<PhysicalObject>>:
void MacroParticle::setBoundaryElements(Shape* _shape, State* _state)
{
    physicalMesh_->setBoundaryElements(_shape, _state);
    physMeshFlag_ = true;
}
State* MacroParticle::getState_()
{
    return state_;
}

}


