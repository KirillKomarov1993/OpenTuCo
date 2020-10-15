#ifndef ELEMENT_H
#define ELEMENT_H

#include "mathlist.h"

namespace phonon {

struct Element
{
    double mass;
    double radius;
    std::string name;
    Element()
    {

    }
    double getMass()
    {
        return mass;
    }
    std::string getName()
    {
        return name;
    }
};

struct Carboneum : Element
{
    Carboneum ()
    {
        name = "C";
        mass = 1.0;
        radius = 1.0;
    }
};

struct Ferrum : Element
{
    Ferrum()
    {
        name = "Fe";
        mass = 1.0;
        radius = 1.0;
    }
};

}

#endif // ELEMENT_H
