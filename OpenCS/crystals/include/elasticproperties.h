#ifndef ELASTICPROPERTIES_H
#define ELASTICPROPERTIES_H

#include "mathlist.h"
#include "physlist.h"
#include "unitcell.h"
#include "structure.h"
#include "energy.h"

namespace cs {


struct InternalTensor
{
    InternalTensor(int _indice) :
        indice(_indice)
    {

    }
    void setModule(int _j, Matrix3d& _module)
    {
        modules[_j] = _module;
    }
    Matrix3d getModule(int _j)
    {
        return modules[_j];
    }
    double getModule(int _j, int _alpha1, int _alpha2)
    {
        return modules[_j](_alpha1, _alpha2);
    }
protected:
    int indice;
    std::map<int, Matrix3d> modules;
};



struct ElasticProperties
{
    std::vector<InternalTensor> tensors;
    ElasticProperties()
    {
        tensors.push_back(InternalTensor(1));
        tensors.push_back(InternalTensor(2));
    }
    InternalTensor* getInternalTensor(unsigned long _number)
    {
        return &tensors[_number - 1];
    }
};

}

#endif // ELASTICPROPERTIES_H
