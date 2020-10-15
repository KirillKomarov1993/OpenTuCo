#ifndef UNITCELL_H
#define UNITCELL_H

#include <memory>

#include "mathlist.h"
#include "particle.h"
//#include "energy.h"
#include "node.h"
#include "virtualshift.h"

namespace cs {

struct UnitCell
{
    UnitCell();
    UnitCell(unsigned long _number, Vector3d _n);
    UnitCell(unsigned long number, Vector3d n, std::vector<Node*> nodes);
    void clear();
    void setNode(Node* _nude);
    void setCellEnergy(ph::Energy& energy);
    //!*Новые методы и функции:
    void setVirtualShift(VirtualShift* _shift);
    void removeVirtualShift();

    unsigned long getNumber();
    unsigned long getParticleCount();
    bool isEmpty();
    Vector3d getPosition();
    ph::Energy* getCellEnergy();
    Node* getNode(unsigned long _number);
    std::vector<Node*>* getNodes();

    bool operator ==(const UnitCell *_cell) const;
    bool operator !=(const UnitCell *_cell) const;
    bool operator <( UnitCell *_cell);
    bool operator >( UnitCell *_cell);
    bool operator <(const UnitCell& _cell) const;
    std::vector<Node*> nodes_;
private:
    unsigned long number_;
    unsigned long numNudes_;
    Vector3d n_;
    ph::Energy energy;


};

}

#endif // UNITCELL_H
