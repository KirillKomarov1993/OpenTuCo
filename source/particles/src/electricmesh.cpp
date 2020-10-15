#include "electricmesh.h"

namespace tuco {

ElectricMesh::ElectricMesh()
{

}
ElectricMesh::~ElectricMesh()
{

}
void ElectricMesh::setBoundaryElements(Shape* _shape, State* _state)
{
    numElements = 0;
    for (auto &iPolygon : _shape->mesh->polygones)
    {
        boundaryElements.push_back(new ElectricElement(&iPolygon, _state));
        numElements++;
    }
}
unsigned short ElectricMesh::getElementCount()
{
    return numElements;
}
std::vector<BoundaryElement*>* ElectricMesh::getBoundaryElements()
{
    return &boundaryElements;
}

}
