#include "kernalset.h"

namespace tuco {


//! Обычные ядра, К1 и К1*:
    double GreenKernelFunction::getKernal1(Vector3d _r1, Vector3d _r2)
    {
        return greenKernel->getFunction(_r1, _r2);
    }
    double GreenKernelFunction::getPseudoKernal1(Vector3d _r1, Vector3d _r2)
    {
        return greenKernel->getFunction(_r1, _r2);
    }
//! Градиентные ядра, К2 и К2*:
    double GreenKernelFunction::getKernal2(Vector3d _r1, Vector3d _r2)
    {
        return (element2->getNormal()).dot(greenKernel->getGradient(_r1, _r2));
    }
    double GreenKernelFunction::getPseudoKernal2(Vector3d _r1, Vector3d _r2)
    {
        return (element1->getNormal()).dot(greenKernel->getGradient(_r1, _r2));
    }
//! Лапласовы ядра, К3 и К3*:
    double GreenKernelFunction::getKernal3(Vector3d _r1, Vector3d _r2)
    {
        n1 = element1->getNormal();
        n2 = element2->getNormal();
        return -(ph::getKronProduct(n2, n1) * greenKernel->getJacobianMatrix(_r1, _r2)).trace();
    }
    double GreenKernelFunction::getPseudoKernal3(Vector3d _r1, Vector3d _r2)
    {
        n1 = element1->getNormal();
        n2 = element2->getNormal();
        return (ph::getKronProduct(n1, n2) * greenKernel->getJacobianMatrix(_r1, _r2)).trace();
    }


}
