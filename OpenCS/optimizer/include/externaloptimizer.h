/************************************************
 * Module: externaloptimizer.h
 * Author: Kirill A. Komarov
 * Modified: 11 Feb 2019 /
 * Purpose: Declaration of the class ExternalOptimizer
*************************************************/

#ifndef EXTERNALOPTIMIZER_H
#define EXTERNALOPTIMIZER_H

#include "optimizationalgorithm.h"

namespace cs {

//**Унаследованный класс:
class ExternalOptimizer : public OptimizationAlgorithm
{
public:
    ExternalOptimizer();
    void find();
};


}

#endif // EXTERNALOPTIMIZER_H
