#ifndef STABILIZATION_H
#define STABILIZATION_H

#include "colloid.h"
#include "medium.h"

namespace tuco {

struct Stabilization
{
    Stabilization()
    {

    }
    std::string getType(const Material* _material1, const Material* _material2)
    {
        return "simply";
    }
    /*
    double getChargeValue(Medium* _medium, Colloid* _particle)
    {
        if (getType(_medium->getMaterial(), _particle->getMaterial()) == "simply") {
            return 0.0;
        }
    }
*/
};

}

#endif // STABILIZATION_H
