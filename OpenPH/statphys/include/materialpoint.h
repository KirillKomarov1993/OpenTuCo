#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H

#include "mathlist.h"

namespace ph {

struct MaterialPoint {
    MaterialPoint()
    {

    }
    MaterialPoint(unsigned long _number, double _mass, Vector3d _r) :
        number(_number), mass(_mass), position(_r)
    {
        //number = NULL;
    }
    MaterialPoint(unsigned long _number, Vector3d _r, Vector3d _v) :
        number(_number), position(_r), velocity(_v)
    {

    }
    void setPosistion(Vector3d _r)
    {
        this->position = _r;
    }
    unsigned long getNumber()
    {
        return number;
    }
    double getMass()
    {
        return mass;
    }
    Vector3d getPosition()
    {
        return position;
    }
    Vector3d getVelocity()
    {
        return velocity;
    }
private:
    unsigned long number;
    double mass;
    Vector3d position;
    Vector3d velocity;
};

}

#endif // MATERIALPOINT_H
