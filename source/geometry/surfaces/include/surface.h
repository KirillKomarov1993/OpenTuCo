#ifndef SURFACE_H
#define SURFACE_H

#include "mathlist.h"
#include "pointlist.h"
#include "mesh.h"

namespace tuco {

class Surface
{
public:
    int number;
    std::string name;
    Vector3d tangent1;
    Vector3d tangent2;
    Mesh* mesh;
    PointList* pointlist;
    Surface(int _number) :
        number(_number)
    {

    }
    virtual void setPointList() = 0;
    virtual void setPointList(int _numNodes1, int _numNodes2) = 0;
};

}

#endif // SURFACE_H
