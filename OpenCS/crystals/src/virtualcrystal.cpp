#include "virtualcrystal.h"


namespace cs {

VirtualCrystal::VirtualCrystal()
{
    //elProperties = new ElasticProperties();
}
VirtualCrystal::~VirtualCrystal()
{

}
void VirtualCrystal::setStructure(std::shared_ptr<Structure> structure)
{
    this->structure = structure;
    mainUnitCell.reset(new UnitCell(1, structure->getMainLattice()->getPosition()));
    unsigned long nNode = 0;
    for (auto& iLattice : structure->getLattices())
    {
        mainUnitCell->setNode(new Node(nNode + 1, iLattice->getPosition(), structure->getParticle(iLattice), iLattice->isMainLattice()));
        nNode++;
    }
}

void VirtualCrystal::define(double _r_cut)
{
    int numNeighbors = static_cast<int>(2.0 * _r_cut / structure->getMainLattice()->getTranslation());
    unsigned long nNode;
    Vector3d n;
    Lattice* lattice = structure->getMainLattice();
    unsigned long nCell = 2;
    for (int i = -numNeighbors; i < numNeighbors; i++)
    {
        for (int j = -numNeighbors; j < numNeighbors; j++)
        {
            n = lattice->getNodePosition(Vector3d(i, j, 0));
            if (i == 0 && j ==0)
            {

            }
            else
            {
                cells.push_back(new UnitCell(nCell, n));
                nCell++;

                nNode = 0;
                for (auto &iLattice : structure->getLattices())
                {
                    if ((n + iLattice->getPosition()).norm() <= _r_cut)
                    {
                        //cells.back()->setNode(new Node(nNode + 1, iLattice->getPosition(), iLattice->getParticle()));
                        cells.back()->setNode(new VirtualNode(mainUnitCell->getNode(nNode), cells.back()));
                        /*
                        VirtualNode* node = new VirtualNode(mainUnitCell->getNode(nNode), cells.back());
                        Node* node_ = node;
                        std::cout << cells.back()->getPosition() << std::endl;
                        std::cout << node_->getPosition() << std::endl;
                        std::cin.get();
                        */
                    }
                    nNode++;
                }
                if (cells.back()->isEmpty()) {
                    cells.pop_back();
                    nCell--;
                }
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
void VirtualCrystal::record(std::string _address, std::string _name)
{
    std::string fullAddress = _address + _name + ".cif"; // .CrystallographicInformationFile
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
    for (auto& iNode : *mainUnitCell->getNodes())
    {
        out << mainUnitCell->getNumber()
            << "  "
            << iNode->getNumber()
            << "  "
            << iNode->getPosition()(0)
            << "  "
            << iNode->getPosition()(1)
            << "\n";
    }
    for (auto &iCell : cells)
    {
        for (auto& iNode : *iCell->getNodes())
        {
            out << iCell->getNumber()
                << "  "
                << iNode->getNumber()
                << "  "
                << iNode->getPosition()(0)
                << "  "
                << iNode->getPosition()(1)
                << "\n";
        }
    }
    out.close();
}
void VirtualCrystal::setVariation(VirtualShift* _shift)
{
    mainUnitCell->setVirtualShift(_shift);
    for (auto& iCell : cells)
    {
        iCell->setVirtualShift(_shift);
    }
}
void VirtualCrystal::removeVariation()
{
    mainUnitCell->removeVirtualShift();
}

}

