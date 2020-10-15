#include "shape.h"

namespace tuco {
Shape::Shape()
{

}
Shape::~Shape()
{
    delete mesh;
}
const std::string Shape::getName() const {
    return name;
}

}
