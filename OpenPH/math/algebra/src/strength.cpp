#include "strength.h"

namespace ph {

Strength::Strength()
{

}
Strength::Strength(Vector3d _r) :
    r(_r)
{
    strength = Eigen::Vector3d(0.0, 0.0, 0.0);
}
Strength::Strength(Vector3d _strength, Vector3d _r) :
    r(_r), strength(_strength)
{

}
Strength::Strength(Strength const& _strength)
    : r(_strength.r), strength(_strength.strength)
{

}
double Strength::dot(Vector3d _vector)
{
    return strength.dot(_vector);
}
Vector3d Strength::getPosition()
{
    return this->r;
}
Vector3d Strength::getVector()
{
    return this->strength;
}
Strength& Strength::operator=(const Strength& _right) {
    if (this == &_right) {
        return *this;
    }
    strength = _right.strength;
    r = _right.r;
    return *this;
}
Strength& Strength::operator+=(const Strength& _right) {
    if (r == _right.r) {
        strength += _right.strength;
    }
    return *this;
}
const Strength Strength::operator+(const Strength& _right) const {
    return Strength(*this) += _right;
}




void StrengthField::record(std::string _address)
{
    std::string fullAdress = _address + name + ".field";
    std::ofstream out(fullAdress, std::ios::out | std::ios::binary);
    for (auto iterator = strengthes.begin(); iterator != strengthes.end(); ++iterator) {
        //out << iterator.number << "   ";
        for (int alpha = 0; alpha < iterator->r.size(); alpha++)
        {
                out << iterator->r(alpha) << "   ";
        }
        for (int alpha = 0; alpha < iterator->strength.size(); alpha++)
        {
                out << iterator->strength(alpha) << "   ";
        }
        out << "\n";
    }
    out.close();
}


void StrengthField::setElement(Strength _strength)
{
    strengthes.push_back(_strength);
    numStrengthes++;
}

}
