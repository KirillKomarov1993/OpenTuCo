#ifndef NUDE_H
#define NUDE_H

#include <memory>

#include "mathlist.h"
#include "particle.h"

namespace cs {

//!*Здесь узел принадлежит элементраной ячейке <<UnitCell>>, поэтому целесообразно дать ссылку на эту ячейку.
//! Ссылка ПУСТАЯ! И наполять ее без определения НЕЛЬЗЯ! Определение дается ниже.
struct UnitCell;

struct Node
{
    Node();
    Node(unsigned short number, Vector3d r,  Particle* particle, bool flag);
    Node(unsigned long number, Vector3d r, UnitCell* unitCell, Particle* particle) :
        number_(number), r_(r), unitCell_(unitCell), particle_(particle)
    {

    }
    virtual ~Node();
    void setUnitCell(UnitCell& unitCell);
    void setShift(Vector3d u);
    void resetShift();
    void clearShift();
    unsigned short getNumber();
    bool isMainNode();
    virtual Vector3d getPosition();
    UnitCell* getUnitCell();
    Particle* getParticle();
protected:
    unsigned short number_;
    bool flag;
    Vector3d r_;
    Vector3d u_;
    UnitCell* unitCell_;
    Particle* particle_;
    //std::shared_ptr<Particle> particle_;
};

}

#endif // NUDE_H
