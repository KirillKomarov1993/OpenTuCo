#include "object.h"

namespace tuco {

Object::Object()
{

}
Object::Object(Shape *_shape, Material* _material)
    : shape(_shape), material(_material)
{
    mass = shape->volume*material->density;
}
double Object::getMass()
{
    return mass;
}
double Object::getVolume()
{
    return shape->volume;
}
Material* Object::getMaterial()
{
    return material.get();
}
Shape* Object::getShape()
{
    return shape.get();
}

}
