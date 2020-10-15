#include "medium.h"

namespace tuco {

Environment::Environment(Material* material) :
    space_(new Space(3)), green_(new ph::YukawaKernal(material->kappa)), material_(material)
{

}
void Environment::setElectricField(ph::ElectricField* field)
{
    this->field_.reset(field);
}
ph::ElectricField* Environment::getElectricField()
{
    return this->field_.get();
}
void Environment::record(std::string _address, std::string _name)
{

    std::string fullAdress = _address + _name + ".media";
    std::ofstream out(fullAdress, std::ios::out | std::ios::binary);
/*
    out << "Medium:  " << "\n";
    out << material;
*/
    out.close();

}
double Environment::getDebyeLength()
{
    return material_->kappa;
}
ph::GreenKernel* Environment::getCreenCore()
{
    return green_.get();
}
Material* Environment::getMaterial()
{
    return material_.get();
}
Space* Environment::getSpace()
{
    return space_.get();
}

}
