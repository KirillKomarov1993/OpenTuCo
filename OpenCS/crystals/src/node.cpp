#include "node.h"

namespace cs {

Node::Node()
{

}
Node::Node(unsigned short number, Vector3d r,  Particle* particle, bool flag) :
    number_(number), flag(flag), r_(r), u_(Vector3d::Zero())
{
    this->particle_ = particle;
}
Node::~Node()
{

}
void Node::setUnitCell(UnitCell& unitCell)
{
    this->unitCell_ = &unitCell;
}
void Node::setShift(Vector3d u)
{
    this->u_ = u;
}
void Node::resetShift()
{
    this->u_ = Vector3d::Zero();
}
void Node::clearShift()
{
    u_ << 0.0, 0.0, 0.0;
}
unsigned short Node::getNumber()
{
    return number_;
}
bool Node::isMainNode()
{
    return flag;
}
Vector3d Node::getPosition()
{
    return r_ + u_;
}
UnitCell* Node::getUnitCell()
{
    return unitCell_;
}
Particle* Node::getParticle()
{
    return particle_;
}

}
