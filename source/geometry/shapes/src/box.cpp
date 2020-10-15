#include "box.h"

namespace tuco {

Box::Box(double _length, double _width, double _high) :
    length(_length), width(_width), high(_high)
{
    name = "box";
    volume = length * width * high;
    setPolygonMesh();
}
Box::~Box()
{

}
void Box::setPolygonMesh()
{
    mesh = new Mesh(name);
}

}
