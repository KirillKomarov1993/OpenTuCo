#include "electricelement.h"

namespace tuco {


ElectricElement::ElectricElement(Polygon* _polygon, State* _state) :
    BoundaryElement (_polygon, _state)
{
    sigma = 0.0;
    tau = 0.0;
    flagSigma = false;
    flagTau = false;
    //polygon_.reset(_polygon);
    //state_.reset(_state);
}
ElectricElement::ElectricElement(double _chargeDensity,  double _dipoleDensity, Polygon* _polygon) :
    sigma(_chargeDensity), tau(_dipoleDensity)
{
    flagSigma = true;
    flagTau = true;
    polygon_.reset(_polygon);
}
ElectricElement::~ElectricElement()
{

}
void ElectricElement::clear()
{
    sigma = 0;
    tau = 0;
    flagSigma = false;
    flagTau = false;
}
void ElectricElement::setChargeDensity(double _sigma)
{
    sigma = _sigma;
    flagSigma = true;
}
void ElectricElement::setDipoleDensity(double _tau)
{
    tau = _tau;
    flagTau = true;
}
double ElectricElement::getChargeValue()
{
    return sigma * polygon_->area;
}
bool ElectricElement::isCharged()
{
    return flagSigma;
}
bool ElectricElement::isDipoled()
{
    return flagTau;
}
double ElectricElement::getChargeDensity()
{
    return sigma;
}
Vector3d ElectricElement::getDipoleDensity()
{
    return tau * getNormal();
}
Vector3d ElectricElement::getDipoleValue()
{
    return tau * getArea() * getNormal();
}

}
