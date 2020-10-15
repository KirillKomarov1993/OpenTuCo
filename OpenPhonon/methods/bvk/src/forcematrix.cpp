#include "forcematrix.h"

namespace phonon {

ForceTensor::ForceTensor(atom::AtomCrystal* _crystal) :
    crystal(_crystal)
{
    size = crystal->getCountCells();
    setMatrix();
}
void ForceTensor::setMatrix()
{    
    nBlock = 1;
    for (auto& iCell : crystal->getUnitCells())
    {
        if(!crystal->isMainUnitCell(iCell)) {
            blocks.push_back(ForceBlock(nBlock, crystal->getMainUnitCell().get(), iCell, crystal));
            nBlock++;
        }
        else
        {
            blocks.push_back(ForceBlock(0, crystal->getMainUnitCell().get(), iCell, crystal));
        }
    }   
    setDiagonal();
    for (auto &iBlock : blocks)
    {
        iBlock.transform();
    }
}
void ForceTensor::setDiagonal()
{
    for (unsigned long i = 1; i <= crystal->getStructure()->getLatticeCount(); i++)
    {
        matrix_ = MatrixXd::Zero(static_cast<int>(crystal->getDimension()), static_cast<int>(crystal->getDimension()));
        for (auto& iBlock : blocks)
        {
            if (iBlock.getNumber() != 0) {
                matrix_ -= iBlock.sumRows(i);
            }
        }
        for (auto& iBlock : blocks)
        {
            if (iBlock.getNumber() == 0) {
                iBlock.setElement(i, i, matrix_);
            }
        }
    }
}
void ForceTensor::record(std::string _address, std::string _name)
{
    std::string fullAddress = _address + _name + ".fmatrix";
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);

    for (auto iForceCell : blocks)
    {
        for (auto iForceMatrix : iForceCell.getForceCells())
        {
            //out << "nRow = " << iForceMatrix.getRowCount() << ",  nCol = " << iForceMatrix.getColCount() << "\n";
            out << "number = " << iForceCell.getNumber() << "\n";
            out <<  iForceMatrix.getMatrix() << "\n";

            out << "\n";
        }
        out << "\n";
    }
    out.close();
}

}
