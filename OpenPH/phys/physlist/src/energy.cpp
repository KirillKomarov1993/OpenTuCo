#include "energy.h"

namespace ph {


Energy::Energy()
{
    energy = 0.0;
}
Energy::Energy(double _energy) :
    energy(_energy)
{

}
void Energy::clear()
{
    energy = 0.0;
}
void Energy::setValue(double _energy)
{
    energy = _energy;
}
void Energy::addValue(double _energy)
{
    energy += _energy;
}
void Energy::addEnergy(Energy _energy)
{
    energy += _energy.energy;
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
    return *this;
}
Energy& Energy::operator+=(const Energy& _right) {
    energy += _right.energy;
    return *this;
}
Energy& Energy::operator-=(const Energy& _right) {
    energy -= _right.energy;
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
    return this;
}
const Energy Energy::operator/(const double _right) const {
    return Energy(energy / _right);
}

Energy* Energy::operator*(const double _right)
{
    return new Energy(energy * _right);
}

}
