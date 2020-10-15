#include "symplexintegration.h"

namespace tuco {

SymplexIntegration::SymplexIntegration(std::string _type)
{
    type = _type;
    if (type == "linear") {
        setLinearRule();
    }
    if (type == "cubic") {
        setCubicRule();
    }
    if (type == "quadratic") {
        setQuadraticRule();
    }
}
void SymplexIntegration::setLinearRule()
{
    Vector2d epsilon_(2);
    numNodes = 1;
    weightes.push_back(1.0);
    epsilon_ << 1.0/3.0, 1.0/3.0;
    epsilones.push_back(epsilon_);
}
void SymplexIntegration::setQuadraticRule()
{
    numNodes = 3;
    weightes.push_back(1.0/3.0);
    weightes.push_back(1.0/3.0);
    weightes.push_back(1.0/3.0);
    epsilones.push_back(Vector2d(1.0/6.0, 1.0/6.0));
    epsilones.push_back(Vector2d(2.0/3.0, 1.0/6.0));
    epsilones.push_back(Vector2d(1.0/6.0, 2.0/3.0));
}
void SymplexIntegration::setCubicRule()
{
    Vector2d epsilon_(2);
    numNodes = 4;
    weightes.push_back(-27.0/48.0);
    weightes.push_back(+25.0/48.0);
    weightes.push_back(+25.0/48.0);
    weightes.push_back(+25.0/48.0);
    epsilon_ << 1.0/3.0, 1.0/3.0;
    epsilones.push_back(epsilon_);
    epsilon_ << 1.0/5.0, 3.0/5.0;
    epsilones.push_back(epsilon_);
    epsilon_ << 1.0/5.0, 1.0/5.0;
    epsilones.push_back(epsilon_);
    epsilon_ << 3.0/5.0, 1.0/5.0;
    epsilones.push_back(epsilon_);
}
Vector3d SymplexIntegration::getTrianglePosition(unsigned long _nNode, BoundaryElement* _element)
{
    return (1 - epsilones[_nNode](0) - epsilones[_nNode](1)) * _element->getPointPosition("A") +
                                      (epsilones[_nNode](0)) * _element->getPointPosition("B") +
                                      (epsilones[_nNode](1)) * _element->getPointPosition("C");
}
double SymplexIntegration::getIntegral(std::function<double(KernelFunction*, Vector3d, Vector3d)> _function, KernelFunction* _kernal, BoundaryElement* _element1, BoundaryElement* _element2)
{
    _kernal->setBoundaryElements(_element1, _element2);
    integral = 0.0;
    for (unsigned long i = 0; i < numNodes; i++)
    {
        integral += weightes[i] * _function(_kernal, _element1->getBarycenter(), getTrianglePosition(i, _element2));
    }
    return integral * _element2->getArea();
}
double SymplexIntegration::getIntegral(std::function<double(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, Vector3d _r, BoundaryElement* _element)
{
    integral = 0.0;
    for (unsigned long i = 0; i < numNodes; i++)
    {
        integral += weightes[i] * _function(_green, _r, getTrianglePosition(i, _element));
    }
    return integral * _element->getArea();
}
/*
Vector3d SymplexIntegration::getIntegral(std::function<Vector3d(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, BoundaryElement* _element1, BoundaryElement* _element2)
{
    vector = Eigen::Vector3d(0.0, 0.0, 0.0);
    if (!_element2->isNearestElement(_element1))
    {
        for (unsigned long i = 0; i < numNodes; i++)
        {
            vector += weightes[i] * _function(_green, _element1->getBarycenter(), getTrianglePosition(i, _element2));
        }
        return vector * _element2->getArea();
    }
    return vector;
}
*/

}
