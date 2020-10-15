#include "virtualnode.h"

namespace cs {

VirtualNode::VirtualNode(Node* node, UnitCell* unitCell) :
    Node(*node)
{
    this->unitCell_ = unitCell;
}
VirtualNode::VirtualNode(unsigned long number, Vector3d r, UnitCell* unitCell, Particle* particle) :
    Node(number, r, particle, false)
{
    this->unitCell_ = unitCell;
}
Vector3d VirtualNode::getPosition()
{
    return (r_ + u_) + unitCell_->getPosition();
}


}
