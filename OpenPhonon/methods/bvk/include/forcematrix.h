#ifndef FORCEMATRIX_H
#define FORCEMATRIX_H

#include "forceblocks.h"

namespace phonon {

struct ForceTensor
{
    int size;
    atom::AtomCrystal* crystal;
    std::vector<ForceBlock> blocks;
    ForceTensor(atom::AtomCrystal* _crystal);
    void setMatrix();
    void setDiagonal();
    void record(std::string _address, std::string _name);

private:
    int nBlock;
    MatrixXd matrix_;
};

}

#endif // FORCEMATRIX_H
