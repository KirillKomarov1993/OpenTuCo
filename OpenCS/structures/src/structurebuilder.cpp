#include "structurebuilder.h"

namespace cs {

StructureBuilder::~StructureBuilder()
{

}
std::shared_ptr<Structure> StructureBuilder::getStructure()
{
    return structure;
}
void StructureBuilder::createNewStructure()
{
    structure.reset(new Structure);
}


HexagonalStructureBuilder::~HexagonalStructureBuilder()
{

}
void HexagonalStructureBuilder::build()
{
    double trn_ = 1.0;
    structure->setName("hexagonal");
    //structure->setLattice(new Lattice("main", new Hexagonal(trn_), Vector3d(0., 0., 0.)));
    structure->setLatticeGroup(new Lattice("main", new Hexagonal(trn_), Vector3d(0., 0., 0.)), new Particle(1, "simple"));
}


GrapheneStructureBuilder::~GrapheneStructureBuilder()
{

}
void GrapheneStructureBuilder::build()
{
    double trn_ = 1.0;
    structure->setName("graphene");   
    structure->setLatticeGroup(new Lattice("main", new Hexagonal(trn_), Vector3d(0.0, 0.0, 0.0)), new Particle(1, "simple"));
    structure->setLatticeGroup(new Lattice("main", new Hexagonal(trn_), Vector3d(trn_ / 2.0, trn_ / sqrt(3.0)/ 2.0, 0.0)), new Particle(2, "simple"));
}


QuasiStructureBuilder::~QuasiStructureBuilder()
{

}
void QuasiStructureBuilder::build() {
    double trn = 1.0;
    double _coef = 0.25;
    l1 = 1.0 / sqrt(3.0) * (1.0 - 2.0 * _coef) * trn;
    l2 = _coef * trn;
    structure->setName("quasistructure");
    structure->setLatticeGroup(new Lattice("main", new Hexagonal(trn), Vector3d(0.0, 0.0, 0.0)), new Particle(1, "simple"));
    structure->setLatticeGroup(new Lattice("side", new Hexagonal(trn), Vector3d(l1 * sqrt(3.0)/ 2.0, l1 / 2.0, 0.0)), new Particle(2, "simple"));
    structure->setLatticeGroup(new Lattice("side", new Hexagonal(trn), Vector3d(l1 * sqrt(3.0)/ 2.0 + l2, l1 / 2.0, 0.0)), new Particle(3, "simple"));
    structure->setLatticeGroup(new Lattice("side", new Hexagonal(trn), Vector3d(l1 * sqrt(3.0)/ 2.0 + l2 / 2.0, l1 / 2.0 + l2 * sqrt(3.0)/ 2.0, 0.0)), new Particle(4, "simple"));
    structure->setLatticeGroup(new Lattice("side", new Hexagonal(trn), Vector3d(-l2, 0.0, 0.0)), new Particle(5, "simple"));
    structure->setLatticeGroup(new Lattice("side", new Hexagonal(trn), Vector3d(-l2 / 2.0, -l2 * sqrt(3.0) / 2.0, 0.0)), new Particle(6, "simple"));
}



}
