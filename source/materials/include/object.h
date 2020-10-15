#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

#include "materiallist.h"
#include "shape.h"
#include "boundaryelement.h"

namespace tuco {

struct Object
{   
    Object();
    Object(Shape *_shape, Material* _material);
    double getMass();
    double getVolume();
    Material* getMaterial();
    Shape* getShape();
protected:
    double mass;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Material> material;
};

}

#endif // OBJECT_H
