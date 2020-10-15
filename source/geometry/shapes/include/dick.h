#ifndef DICK_H
#define DICK_H

#include "shape.h"

namespace tuco {

struct Disk : Shape
{
    double width;
    Disk(double _radius, double _width) :
        width(_width)
    {
        name = "disk";
        radius = _radius;
        volume = ph::pi() * radius * radius;
        setPolygonMesh();
    }
    ~Disk()
    {

    }
    void setPolygonMesh()
    {
        mesh = new Mesh(name);
    }
};

}

#endif // DICK_H
