#include "integralequation.h"

namespace tuco {

IntegralEquation::IntegralEquation(Integration* _integral) :
    integralSQ_(_integral)
{

}
IntegralEquation::~IntegralEquation()
{
    //delete kernelFunction1_;
    //delete kernelFunction2_;
}
void IntegralEquation::setEnvironment(Environment* _medium)
{
    environment_ = _medium;
    kernelFunction1_ = new GreenKernelFunction(environment_->getCreenCore());
}
unsigned short IntegralEquation::getEquationsSize()
{
    return coef_;
}
bool IntegralEquation::isChargeExist()
{
    return flagCharge_;
}
bool IntegralEquation::isDipoleExist()
{
    return flagDipole_;
}
/*
GreenKernelFunction* IntegralEquation::getGreenKeernalFunction()
{
    return kernelFunction_;
}
*/

}







