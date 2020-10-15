/************************************************
 * Module: methodgradientdescent.h
 * Author: Kirill A. Komarov
 * Modified: 1 Feb 2019 /
 * Purpose: Declaration of the class MethodGradientDescent
*************************************************/

#ifndef METHODGRADIENTDESCENT_H
#define METHODGRADIENTDESCENT_H

#include "optimizationalgorithm.h"

namespace cs {

//**Унаследованный класс:
class MethodGradientDescent : public OptimizationAlgorithm
{
    int maxIterations;
    double lambda;
    double error;
    VectorXd gradient;
public:
    MethodGradientDescent(ph::Functional* functional);
    MethodGradientDescent(VectorXd r, ph::Functional* functional);
    void find();
};

}

#endif // METHODGRADIENTDESCENT_H
