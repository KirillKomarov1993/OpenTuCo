#include "unitcell.h"


namespace cs {

UnitCell::UnitCell()
{

}
UnitCell::UnitCell(unsigned long _number, Vector3d _n) :
    number_(_number), n_(_n)
{
    numNudes_ = 0;
}
UnitCell::UnitCell(unsigned long number, Vector3d n, std::vector<Node*> nodes) :
    number_(number), n_(n), nodes_(nodes)
{
    numNudes_ = nodes.size();
    for (auto& iNode : nodes_)
    {
        iNode->setUnitCell(*this);
    }
}


void UnitCell::clear()
{
    nodes_.clear();
    numNudes_ = 0;
}
void UnitCell::setNode(Node* _nude)
{
    _nude->setUnitCell(*this);
    nodes_.push_back(_nude);
    numNudes_++;
}
void UnitCell::setCellEnergy(ph::Energy &energy)
{
    this->energy = energy;
}
//!*Новые методы и функции:
void UnitCell::setVirtualShift(VirtualShift* _shift)
{
    for (auto& iNode : nodes_)
    {
        if (iNode->getNumber() == _shift->getNodeNumber()) {
            iNode->setShift(_shift->getShift());
            break;
        }
    }
}
void UnitCell::removeVirtualShift()
{
    for (auto& iNode : nodes_)
    {
        iNode->resetShift();
    }
}


unsigned long UnitCell::getNumber()
{
    return number_;
}
unsigned long UnitCell::getParticleCount()
{
    return numNudes_;
}
bool UnitCell::isEmpty()
{
    return nodes_.empty();
}
Vector3d UnitCell::getPosition()
{
    return n_;
}
ph::Energy* UnitCell::getCellEnergy()
{
    return &energy;
}
Node* UnitCell::getNode(unsigned long _number)
{
    return nodes_[_number];
}
std::vector<Node*>* UnitCell::getNodes()
{
    return &nodes_;
}


bool UnitCell::operator ==(const UnitCell *_cell) const
{
    return n_ == _cell->n_;
}
bool UnitCell::operator !=(const UnitCell *_cell) const
{
    return n_ != _cell->n_;
}
bool UnitCell::operator <( UnitCell *_cell)
{
    return number_ < _cell->getNumber();
}
bool UnitCell::operator >( UnitCell *_cell)
{
    return number_ > _cell->getNumber();
}
bool UnitCell::operator <(const UnitCell& _cell) const
{
    return number_ < _cell.number_;
}


}
