#ifndef BOUNDARYELEMENT_H
#define BOUNDARYELEMENT_H

#include <memory>

#include "polygon.h"
#include "state.h"

namespace tuco {

struct  ElectricElement;

struct BoundaryElement
{
    BoundaryElement();
    BoundaryElement(Polygon* _polygon, State* _state);
    virtual ~BoundaryElement();
//**Базовые методы:
    int getNumber();
    double getArea();
    bool isNearestPosition(Vector3d _r);
    bool isNearestElement(BoundaryElement* _element);
    Vector3d getPointPosition(std::string _name);
    Vector3d getNormal();
    Vector3d getBarycenter();
    Polygon* getPolygon();
    State* getState()
    {
        return state_;
    }
//**Абсолютно виртуальные методы:
    virtual void clear() = 0;
    virtual void setChargeDensity(double) = 0;
    virtual void setDipoleDensity(double) = 0;    
    virtual bool isCharged() = 0;
    virtual bool isDipoled() = 0;
    virtual double getChargeValue() = 0;
    virtual Vector3d getDipoleValue() = 0;
    virtual double getChargeDensity() = 0;
    virtual Vector3d getDipoleDensity() = 0;
//**Дружественные функции:
    friend std::ostream& operator << (std::ostream& _flux, BoundaryElement* _element)
    {
      std::ios::fmtflags mode = _flux.flags();
      _flux.setf(std::ios::fixed,std::ios::floatfield);
      auto prec = _flux.precision(3);

      _flux << std::setw(4) << _element->getNumber() << "   "
            << std::setw(4) << _element->getChargeDensity();// << "   "
            //<< std::setw(4) << _element->getDipoleValue();
      _flux.precision(prec);
      _flux.setf(mode,std::ios::floatfield);
      return _flux;
    }
protected:
    std::shared_ptr<Polygon> polygon_;
    //std::shared_ptr<State> state_;
    State* state_;
};


}


#endif // BOUNDARYELEMENT_H
