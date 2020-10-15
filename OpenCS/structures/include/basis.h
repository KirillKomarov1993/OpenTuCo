#ifndef BASIS_H
#define BASIS_H

#include "mathlist.h"

namespace cs {

struct Basis
{
    unsigned long dim;
    std::vector<Vector3d> a;
    Basis(Vector3d _a1)
    {
        dim = 1;
        a.push_back(_a1);
    }
    Basis(Vector3d _a1, Vector3d _a2)
    {
        dim = 2;
        a.push_back(_a1);
        a.push_back(_a2);
    }
    Basis(Vector3d _a1, Vector3d _a2, Vector3d _a3)
    {
        dim = 3;
        a.push_back(_a1);
        a.push_back(_a2);
        a.push_back(_a3);
    }
    void setBasisVector(Vector3d _a1)
    {
        a.push_back(_a1);
        dim++;
    }
    unsigned long getDimension()
    {
        return dim;
    }
    Vector3d getBasisVector(unsigned long _number)
    {
        return a[_number - 1];
    }
};

}

#endif // BASIS_H
