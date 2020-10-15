#ifndef KERNALSET_H
#define KERNALSET_H

#include "mathlist.h"
#include "greenkernal.h"
#include "boundaryelement.h"

namespace tuco {

struct KernelFunction
{
    KernelFunction()
    {

    }
    virtual ~KernelFunction()
    {

    }
    void setBoundaryElements(BoundaryElement* _element1, BoundaryElement* _element2)
    {
        element1 = _element1;
        element2 = _element2;
    }
//! Обычные ядра, К1 и К1*:
    virtual double getKernal1(Vector3d _r1, Vector3d _r2) = 0;
    virtual double getPseudoKernal1(Vector3d _r1, Vector3d _r2) = 0;
//! Градиентные ядра, К2 и К2*:
    virtual double getKernal2(Vector3d _r1, Vector3d _r2) = 0;
    virtual double getPseudoKernal2(Vector3d _r1, Vector3d _r2) = 0;
//! Лапласовы ядра, К3 и К3*:
    virtual double getKernal3(Vector3d _r1, Vector3d _r2) = 0;
    virtual double getPseudoKernal3(Vector3d _r1, Vector3d _r2) = 0;
protected:
    Vector3d n1, n2;
    BoundaryElement* element1;
    BoundaryElement* element2;
};

struct GreenKernelFunction : public KernelFunction
{
    GreenKernelFunction(ph::GreenKernel* _green) :
        greenKernel(_green)
    {

    }
//! Обычные ядра, К1 и К1*:
    double getKernal1(Vector3d _r1, Vector3d _r2);
    double getPseudoKernal1(Vector3d _r1, Vector3d _r2);
//! Градиентные ядра, К2 и К2*:
    double getKernal2(Vector3d _r1, Vector3d _r2);
    double getPseudoKernal2(Vector3d _r1, Vector3d _r2);
//! Лапласовы ядра, К3 и К3*:
    double getKernal3(Vector3d _r1, Vector3d _r2);
    double getPseudoKernal3(Vector3d _r1, Vector3d _r2);

protected:
    ph::GreenKernel* greenKernel;
};

}


#endif // KERNALSET_H
