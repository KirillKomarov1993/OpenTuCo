#include "crystal.h"


namespace cs {

Crystal::Crystal()
{
    elasticModulus = new ElasticModulus;
}
Crystal::~Crystal()
{

}
/*
void Crystal::setStructure(std::shared_ptr<Structure> structure)
{
    this->structure = structure;
}
*/
unsigned long Crystal::getCountCells()
{
    return numCells;
}
bool Crystal::isMainUnitCell(Node* node) {
    return node->getUnitCell() == mainUnitCell.get();
}
bool Crystal::isMainUnitCell(UnitCell* unitCell) {
    return unitCell == mainUnitCell.get();
}
std::shared_ptr<Structure> Crystal::getStructure()
{
    return structure;
}
std::shared_ptr<UnitCell> Crystal::getMainUnitCell()
{
    return  mainUnitCell;
}
std::vector<UnitCell*> Crystal::getUnitCells()
{
    return cells;
}

}



