#ifndef ELECTRICELEMENT_H
#define ELECTRICELEMENT_H

#include "boundaryelement.h"

namespace tuco {

struct ElectricElement : public BoundaryElement
{
    ElectricElement(Polygon* _polygon, State* _state);
    ElectricElement(double _chargeDensity,  double _dipoleDensity, Polygon* _polygon);
    ~ElectricElement();
//**Базовые методы и функции:
    void clear();
    void setChargeDensity(double _sigma);
    void setDipoleDensity(double _tau);    
    bool isCharged();
    bool isDipoled();
    double getChargeDensity();
    Vector3d getDipoleDensity();
    double getChargeValue();
    Vector3d getDipoleValue();    
protected:
    double sigma;
    double tau;
    bool flagSigma;
    bool flagTau;
};

}

#endif // ELECTRICELEMENT_H
