#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include "mathlist.h"

namespace ph {

struct Functional
{
    Functional()
    {

    }
    virtual ~Functional()
    {

    }
    virtual void setNewArgumentVector(VectorXd) = 0;
    virtual double getFunctionalValue() = 0;
    virtual VectorXd getArgumentVector() = 0;
    virtual VectorXd getGradientVector() = 0;
};

struct RosenbrockFunctional : public Functional
{
    RosenbrockFunctional()
    {

    }
    void setNewArgumentVector(VectorXd argVector)
    {
        this->argVector_ =  argVector;
    }
    double getFunctionalValue()
    {
        return pow(1.0 -  argVector_(1), 2) + 100.0 * pow( argVector_(2) -  argVector_(1) *  argVector_(1), 2);
    }
    VectorXd getArgumentVector()
    {
        return this->argVector_;
    }
    VectorXd getGradientVector()
    {
        VectorXd gradient(3);
        gradient << -2.0 * (1.0 -  argVector_(0)) - 400.0 *  argVector_(0) * ( argVector_(1) -  argVector_(0) *  argVector_(0)),
                                              200.0        * ( argVector_(1) -  argVector_(0) *  argVector_(0)), 0.0;
        return gradient;
    }
private:
    VectorXd  argVector_;
};

}

#endif // FUNCTIONAL_H
