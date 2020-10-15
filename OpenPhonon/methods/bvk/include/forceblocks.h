#ifndef FORCEBLOCKS_H
#define FORCEBLOCKS_H

#include "atomcrystal.h"
#include "atom.h"

namespace phonon {

struct ForceCell
{    
    ForceCell(atom::Atom* _atom1, atom::Atom* _atom2, atom::AtomCrystal* crystal)
    {
        nRow = _atom1->getNumber();
        nCol = _atom2->getNumber();
        size = crystal->getDimension();
        setCell(_atom1, _atom2);
    }
    void setCell(atom::Atom* _atom1, atom::Atom* _atom2)
    {
        dr_ = _atom1->getPosition() - _atom2->getPosition();
        matrix = MatrixXd::Zero(size, size);
        for (int alpha = 0; alpha < size; alpha++)
        {
            for (int beta = 0; beta < size; beta++)
            {
                if (dr_.norm() != 0) {
                    matrix(alpha, beta) = - _atom1->getPotential(_atom2)->get2Dirivate(alpha, beta, dr_) / sqrt(_atom1->getMass() * _atom2->getMass());
                }
            }
        }
    }
    void setCell(MatrixXd _matrix)
    {
        size = static_cast<int>(sqrt(static_cast<double>(_matrix.size())));
        matrix = _matrix;
    }
    unsigned short getRowNumber()
    {
        return nRow;
    }
    unsigned short getColNumber()
    {
        return nCol;
    }
    MatrixXd getMatrix()
    {
        return matrix;
    }
private:
    int size;
    unsigned short nRow;
    unsigned short nCol;
    MatrixXd matrix;
    Vector3d dr_;
};


struct ForceBlock
{
    ForceBlock(int _number, cs::UnitCell* _cell_1, cs::UnitCell* _cell_2, atom::AtomCrystal* crystal) :
        number(_number)
    {
        dn = _cell_1->getPosition() - _cell_2->getPosition();
        size_ = crystal->getDimension();
        setBlocks(_cell_1, _cell_2, crystal);
    }
    void setBlocks(cs::UnitCell* _cell_1, cs::UnitCell* _cell_2, atom::AtomCrystal* crystal)
    {
        for (auto& iNode_1 : *_cell_1->getNodes())
        {
            for (auto& iNode_2 : *_cell_2->getNodes())
            {
                cells.push_back(ForceCell(crystal->getAtom(iNode_1), crystal->getAtom(iNode_2), crystal));
            }
        }
    }
    void setElement(int _i, int _j, MatrixXd _matrix)
    {        
        for (auto& iCell : cells)
        {
            if (iCell.getColNumber() == _i && iCell.getRowNumber()== _j)
            {
                iCell.setCell(_matrix);
                break;
            }
        }
    }
    int getNumber()
    {
        return number;
    }
    VectorXd getPosition()
    {
        return dn;
    }
    MatrixXd* getMatrix()
    {
        return &matrix;
    }
    MatrixXd sumRows(int _nRow)
    {
        MatrixXd A = MatrixXd::Zero(size_, size_);
        for (auto iCell : cells)
        {
            if (iCell.getRowNumber() == _nRow)
            {
                A += iCell.getMatrix();
            }            
        }
        return A;
    }
    std::vector<ForceCell> getForceCells()
    {
        return cells;
    }
    void transform()
    {
        int numNodes = sqrt(cells.size());
        matrix = MatrixXd::Zero(numNodes * size_, numNodes * size_);
        for (int j = 0; j < numNodes; j++)
        {
            for (int i = 0; i < numNodes; i++)
            {
                matrix.block(j * size_, i * size_, size_, size_) = cells[i + j * numNodes].getMatrix();
            }
        }
        cells.clear();
    }
private:
    int size_;
    int number;
    Vector3d dn;
    std::vector<ForceCell> cells;
    MatrixXd matrix;
};

}

#endif // FORCEBLOCKS_H
