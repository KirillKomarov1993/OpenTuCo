#ifndef STRUCTUREBUILDER_H
#define STRUCTUREBUILDER_H

#include <memory>
#include "structure.h"
#include "lattice.h"

namespace cs {

// Abstract Builder:
class StructureBuilder
{
protected:
    std::shared_ptr<Structure> structure;
public:
    StructureBuilder() {}
    virtual ~StructureBuilder();
    std::shared_ptr<Structure> getStructure();
    void createNewStructure();
    virtual void build() = 0;
};

//ConcreteBuilders (Example & Realization):
class HexagonalStructureBuilder : public StructureBuilder
{
public:
    HexagonalStructureBuilder() : StructureBuilder() {}
    ~HexagonalStructureBuilder();
    void build();
};

class GrapheneStructureBuilder : public StructureBuilder
{
public:
    GrapheneStructureBuilder() : StructureBuilder() {}
    ~GrapheneStructureBuilder();
    void build();
};


class QuasiStructureBuilder : public StructureBuilder
{
    double l1;
    double l2;
public:
    QuasiStructureBuilder() : StructureBuilder() {}
    ~QuasiStructureBuilder();
    void build();

};


}


#endif // STRUCTUREBUILDER_H
