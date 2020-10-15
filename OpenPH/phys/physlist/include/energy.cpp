#include "energy.h"

namespace ph {

Energy::Energy()
{
    energy = 0.0;
    type = "simply";
}
Energy::Energy(std::string _type) :
    type(_type)
{
    energy = 0.0;
}
Energy::Energy(double _energy, std::string _type) :
    energy(_energy), type(_type)
{

}
void Energy::clear()
{
    energy = 0.0;
}
void Energy::setEnergy(double _energy)
{
    energy = _energy;
}
void Energy::addEnergy(double _energy)
{
    energy += _energy;
}
void Energy::addEnergy(Energy* _energy)
{
    energy += _energy->energy;
}
Energy& Energy::operator=(const Energy& right) {
    if (this == &right) {
        return *this;
    }
    energy = right.energy;
    type = right.type;
    return *this;
}
Energy& Energy::operator+=(const Energy& _right) {
    if (type == _right.type) {
        energy += _right.energy;
    }
    return *this;
}
Energy& Energy::operator-=(const Energy& _right) {
    if (type == _right.type) {
        energy -= _right.energy;
    }
    return *this;
}
const Energy Energy::operator+(const Energy& _right) const {
    return Energy(*this) += _right;
}
const Energy Energy::operator-(const Energy& _right) const {
    return Energy(*this) -= _right;
}
Energy* Energy::operator=(const Energy* right) {
    if (this == right) {
        return this;
    }
    energy = right->energy;
    type = right->type;
    return this;
}
const Energy Energy::operator/(const double _right) const {
    return Energy(energy / _right, type);
}
/*
const Energy operator*(const double _right) const {
    return Energy(energy * _right, type);
}
*/
Energy* Energy::operator*(const double _right)
{
    return new Energy(energy * _right, type);
}

}
