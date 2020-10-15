#include "montecarlointegration.h"

namespace tuco {

MonteCarloIntegration::MonteCarloIntegration(std::string _type, unsigned long _numNudes)
{
    numNodes = _numNudes;
    type = _type;
}
double MonteCarloIntegration::getIntegral(std::function<double(KernelFunction*, Vector3d, Vector3d)> _function, KernelFunction* _kernal, BoundaryElement* _element1, BoundaryElement* _element2)
{
    _kernal->setBoundaryElements(_element1, _element2);
    srand(time(NULL));
    integral = 0.0;
    for (int i = 0; i < numNodes; i++)
    {
        s1 = rand() / static_cast<double>(RAND_MAX);
        s2 = rand() / static_cast<double>(RAND_MAX);
        point = _element2->getPointPosition("A") * (1.0 - sqrt(s1))  +
                _element2->getPointPosition("B") * (1.0 - s2) * sqrt(s1) +
                _element2->getPointPosition("C") * s2 * sqrt(s1);
        integral += _function(_kernal, _element1->getBarycenter(), point);
    }
    return integral * _element2->getArea() / static_cast<double>(numNodes);
}
double MonteCarloIntegration::getIntegral(std::function<double(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, Vector3d _r, BoundaryElement* _element)
{
    srand(time(NULL));
    integral = 0.0;
    for (unsigned long i = 0; i < numNodes; i++)
    {
        s1 = rand() / static_cast<double>(RAND_MAX);
        s2 = rand() / static_cast<double>(RAND_MAX);
        point = _element->getPointPosition("A") * (1.0 - sqrt(s1))  +
                _element->getPointPosition("B") * (1.0 - s2) * sqrt(s1) +
                _element->getPointPosition("C") * s2 * sqrt(s1);
        integral += _function(_green, _r, point);
    }
    return integral * _element->getArea() / static_cast<double>(numNodes);
}
/*
Vector3d getIntegral(std::function<Vector3d(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, BoundaryElement* _element1, BoundaryElement* _element2)
{
    return Vector3d(0.0, 0.0, 0.0);
}
*/


}
