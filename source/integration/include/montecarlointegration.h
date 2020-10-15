#ifndef MONTECARLOINTEGRATION_H
#define MONTECARLOINTEGRATION_H

#include "integration.h"
#include <time.h>

namespace tuco {

struct MonteCarloIntegration : public Integration
{
    MonteCarloIntegration(std::string _type, unsigned long _numNudes);
    double getIntegral(std::function<double(KernelFunction*, Vector3d, Vector3d)> _function, KernelFunction* _kernal, BoundaryElement* _element1, BoundaryElement* _element2);
    double getIntegral(std::function<double(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, Vector3d _r, BoundaryElement* _element);
    //Vector3d getIntegral(std::function<Vector3d(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, BoundaryElement* _element1, BoundaryElement* _element2);
private:
    double s1, s2;
    //double integral;
    Vector3d point;
};

}

#endif // MONTECARLOINTEGRATION_H
