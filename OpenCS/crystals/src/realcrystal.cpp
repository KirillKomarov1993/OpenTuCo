#include "realcrystal.h"

namespace cs {

RealCrystal::RealCrystal()
{

}
RealCrystal::~RealCrystal()
{

}

void RealCrystal::setStructure(std::shared_ptr<Structure> structure)
{
    this->structure = structure;
}
void RealCrystal::define(double _r_cut)
{
    int numNeighbors = static_cast<int>(2 * _r_cut / structure->getMainLattice()->getTranslation());
    unsigned long nNode;
    Vector3d n;
    Lattice* lattice = structure->getMainLattice();
    unsigned long nCell = 1;
    for (int i = -numNeighbors; i < numNeighbors; i++)
    {
        for (int j = -numNeighbors; j < numNeighbors; j++)
        {
            n = lattice->getNodePosition(Vector3d(i, j, 0));
            if (i == 0 && j ==0)
            {
                cells.push_back(new UnitCell(0, n));
                mainUnitCell.reset(cells.back());
            }
            else
            {
                cells.push_back(new UnitCell(nCell, n));
                nCell++;
            }
            nNode = 0;
            for (auto &iLattice : structure->getLattices())
            {
                if ((n + iLattice->getPosition()).norm() <= _r_cut)
                {
                    cells.back()->setNode(new Node(nNode + 1, n + iLattice->getPosition(), structure->getParticle(iLattice), iLattice->isMainLattice()));
                    //cells.back()->setNode(new Node(nNode + 1, iLattice->getPosition(), structure->getParticle(iLattice)));
                }
                nNode++;
            }
            if (cells.back()->isEmpty()) {
                cells.pop_back();
                nCell--;
            }
        }
    }
    numCells = nCell;
    //std::sort(*cells.begin(), *cells.end());
    /*
    std::sort(cells.begin(), cells.end(), [](UnitCell _cell1, UnitCell _cell2) {
         return _cell1.getNumber() < _cell2.getNumber();
      });
    */
}
void RealCrystal::record(std::string _address, std::string _name)
{
    std::string fullAddress = _address + _name + ".cif"; // .CrystallographicInformationFile
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
    for (auto &iCell : cells)
    {
        for (auto& iNude : *iCell->getNodes())
        {
            out << iCell->getNumber()
                << "  "
                << iNude->getNumber()
                << "  "
                << iNude->getPosition()(0)
                << "  "
                << iNude->getPosition()(1)
                << "\n";
        }
    }
    out.close();
}
void RealCrystal::setVariation(VirtualShift* _shift)
{
    for (auto& iCell : cells)
    {
        iCell->setVirtualShift(_shift);
    }
}
void RealCrystal::removeVariation()
{
    for (auto& iCell : cells)
    {
        iCell->removeVirtualShift();
    }
}

}
