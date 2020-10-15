#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "kernalset.h"
#include "boundaryelement.h"


namespace tuco {

//Интерфейс:
struct Integration
{    
    Integration();
    virtual ~Integration();
//**Абсолютно виртуальные функции и методы:
    virtual double getIntegral(std::function<double(KernelFunction*, Vector3d, Vector3d)> _function, KernelFunction* _kernal, BoundaryElement* _element1, BoundaryElement* _element2) = 0;
    virtual double getIntegral(std::function<double(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, Vector3d _r, BoundaryElement* _element) = 0;
    //virtual Vector3d getIntegral(std::function<Vector3d(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, BoundaryElement* _element1, BoundaryElement* _element2) = 0;
protected:
    unsigned long numNodes;
    std::string type;
    double integral;
    Vector3d vector;
};


}

#endif // INTEGRATION_H
