#ifndef SPACE_H
#define SPACE_H

#include "mathlist.h"

namespace tuco {

struct Space
{
    unsigned long dim;
    std::string system;
    std::vector<VectorXd> e;
    Space(unsigned long _dim) :
        dim(_dim)
    {

    }
    Space(unsigned long _dim, std::string _system) :
        dim(_dim), system(_system)
    {
        if (system == "cartesian") {
            MatrixXd I = MatrixXd::Identity(static_cast<int>(dim), static_cast<int>(dim));
            for (unsigned long i = 0; i < dim; i++)
            {
                e.push_back(I.row(static_cast<int>(dim)));
            }
        }
    }
    auto getDimenision()
    {
        return dim;
    }
};

}



#endif // SPACE_H
