#ifndef VIRTUALNODE_H
#define VIRTUALNODE_H

#include "node.h"
#include "unitcell.h"

namespace cs {
/*
struct VirtualNode : public Node
{
    VirtualNode(Node* node, UnitCell* unitCell)
    {

    }
    VirtualNode(unsigned long number, Vector3d r, UnitCell* unitCell, Particle* particle) :
        Node(number, r, unitCell, particle)
    {
    }
    ~VirtualNode() override
    {

    }
    void setUnitCell(UnitCell& unitCell)
    {
        node_->setUnitCell(unitCell);
    }
    void setShift(Vector3d u)
    {
        node_->setShift(u);
    }
    void resetShift()
    {
        node_->resetShift();
    }
    void clearShift()
    {
        node_->clearShift();
    }
    unsigned short getNumber()
    {
        return node_->getNumber();
    }
    bool isMainNode()
    {
        return node_->isMainNode();
    }
    UnitCell* getUnitCell()
    {
        return node_->getUnitCell();
    }
    Particle* getParticle()
    {
        return node_->getParticle();
    }
    Vector3d getPosition() override
    {
        return node_->getPosition() + node_->getUnitCell()->getPosition();
    }
private:
    Node* node_;
};
*/

struct VirtualNode : public Node
{
    VirtualNode(Node* node, UnitCell* unitCell);
    VirtualNode(unsigned long number, Vector3d r, UnitCell* unitCell, Particle* particle);
    Vector3d getPosition() override;
};

}


#endif // VIRTUALNODE_H
