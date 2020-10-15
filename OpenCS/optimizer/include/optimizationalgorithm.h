/************************************************
 * Module: optimizationalgorithm.h
 * Author: Kirill A. Komarov
 * Modified: 1 Feb 2019 /
 * Purpose: Declaration of the class OptimizationAlgorithm
*************************************************/

#ifndef OPTIMIZATIONALGORITHM_H
#define OPTIMIZATIONALGORITHM_H

#include "crystal.h"
#include "functional.h"

namespace cs {

//**Базовый класс:
class OptimizationAlgorithm
{
protected:
    std::shared_ptr<ph::Functional> functional;
public:
    OptimizationAlgorithm();
    virtual ~OptimizationAlgorithm();
//**Абсолютно виртуальные функции и методы:
    virtual void find() = 0;
};

}




#endif // OPTIMIZATIONALGORITHM_H
