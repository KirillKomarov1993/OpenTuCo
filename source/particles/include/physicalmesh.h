#ifndef PHYSICALMESH_H
#define PHYSICALMESH_H

#include "boundaryelement.h"
#include "electricelement.h"
#include "object.h"

namespace tuco {

struct PhysicalMesh
{
    PhysicalMesh();
    virtual ~PhysicalMesh();
    virtual void record(std::string _address, std::string _name) = 0;
    virtual void setBoundaryElements(Shape* _shape, State* _state) = 0;
    virtual unsigned short getElementCount() = 0;
    virtual std::vector<BoundaryElement*>* getBoundaryElements() = 0;
};

}
#endif // PHYSICALMESH_H
