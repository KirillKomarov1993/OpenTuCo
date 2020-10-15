#ifndef DEFORMATIONMETHOD_H
#define DEFORMATIONMETHOD_H

#include "crystal.h"

namespace cs {

//
//      здесь, расчет модулей упругости каждого "свободного" узла ячейки
//

// Interface:
class DeformationMethod
{
protected:
    Crystal* crystal;
public:
    DeformationMethod(Crystal* crystal) :
        crystal(crystal)
    {
    }
};

// Realization1:
class InternalDeformationMethod : public DeformationMethod
{
    double step_;
    ph::Energy energy_;
    std::vector<Vector3d> variatons_;
public:
    InternalDeformationMethod(Crystal* crystal, double _step);
    virtual ~InternalDeformationMethod();
    void computerElasticModules();
    virtual void computerCellEnergy() = 0;
protected:
    ph::Energy* energy1;
    ph::Energy* energy2;
};

}


#endif // DEFORMATIONMETHOD_H
