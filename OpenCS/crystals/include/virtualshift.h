#ifndef VIRTUALSHIFT_H
#define VIRTUALSHIFT_H

#include "mathlist.h"

namespace cs {

struct VirtualShift
{
    unsigned long nNode;
    Vector3d u;
    VirtualShift(unsigned long _nNode, Vector3d _u) :
        nNode(_nNode), u(_u)
    {

    }
    unsigned long getNodeNumber()
    {
        return nNode;
    }
    Vector3d getShift()
    {
        return u;
    }

};

}

#endif // VIRTUALSHIFT_H
