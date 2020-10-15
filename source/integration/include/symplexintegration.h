#ifndef SYMPLEXINTEGRATION_H
#define SYMPLEXINTEGRATION_H

#include "integration.h"

namespace tuco {

struct SymplexIntegration : public Integration
{
    SymplexIntegration(std::string _type);
//**Базовые методы и функции:
    void setLinearRule();
    void setQuadraticRule();
    void setCubicRule();
    Vector3d getTrianglePosition(unsigned long _nNode, BoundaryElement* _element);
//**Реализация виртуальных функций:
    double getIntegral(std::function<double(KernelFunction*, Vector3d, Vector3d)> _function, KernelFunction* _kernal, BoundaryElement* _element1, BoundaryElement* _element2);
    double getIntegral(std::function<double(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, Vector3d _r, BoundaryElement* _element);
    //Vector3d getIntegral(std::function<Vector3d(ph::GreenKernel*, Vector3d, Vector3d)> _function, ph::GreenKernel* _green, BoundaryElement* _element1, BoundaryElement* _element2);
private:
    std::vector<double> weightes;
    std::vector<Vector2d> epsilones;
};

}

#endif // SYMPLEXINTEGRATION_H
