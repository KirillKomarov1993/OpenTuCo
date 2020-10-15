#ifndef POINT_H
#define POINT_H

#include "mathlist.h"

namespace tuco {

struct Point
{
    int number;
    Vector3d r;
    Point()
    {

    }
    Point(int _number, Vector3d _r) :
        number(_number), r(_r)
    {

    }
    friend std::ostream& operator << (std::ostream& _flux, const Point* _point)
    {
      std::ios::fmtflags mode = _flux.flags();
      _flux.setf(std::ios::fixed, std::ios::floatfield);
      auto prec = _flux.precision(3);

      _flux
        << _point->number << "   ";
      for (int alpha = 0; alpha < _point->r.size(); alpha++)
      {
        _flux << std::setw(5) << _point->r(alpha) << "  ";
      }

      _flux.precision(prec);
      _flux.setf(mode,std::ios::floatfield);
      return _flux;
    }
};

}

#endif // POINT_H
