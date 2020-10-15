#include "methodgradientdescent.h"

namespace cs {

MethodGradientDescent::MethodGradientDescent(ph::Functional* functional)
{
    maxIterations = 1000;
    lambda = 0.001;
    error = 1e-5;
    this->functional.reset(functional);
}
MethodGradientDescent::MethodGradientDescent(VectorXd r, ph::Functional* functional)
{
    maxIterations = 1000;
    lambda = 0.001;
    error = 1e-5;
    this->functional.reset(functional);
    this->functional->setNewArgumentVector(r);
}
void MethodGradientDescent::find()
{
    gradient = functional->getGradientVector();
    while (gradient.norm() > error) {
        functional->setNewArgumentVector(functional->getArgumentVector() - lambda * gradient);
        gradient = functional->getGradientVector();
    }
}

}
