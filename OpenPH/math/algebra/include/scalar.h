#ifndef SCALAR_H
#define SCALAR_H

#include "mathlist.h"

namespace ph {

struct Scalar
{
    Vector3d r;
    double scalar;    
    Scalar();
    Scalar(Vector3d _r);
    Scalar(double _scalar, Vector3d _r);
    Scalar(Scalar const& _scalar);
    virtual ~Scalar();
    Scalar& operator=(const Scalar& right);
    Scalar& operator+=(const Scalar& _right);
    Scalar& operator-=(const Scalar& _right);
    const Scalar operator+(const Scalar& _right) const;
    const Scalar operator-(const Scalar& _right) const;
    friend std::ostream& operator << (std::ostream& _flux, const Scalar* _scalar)
    {
      std::ios::fmtflags mode = _flux.flags();
      _flux.setf(std::ios::fixed,std::ios::floatfield);
      auto prec = _flux.precision(3);

      _flux
        << std::setw(4) << _scalar->r(0) << " " <<  _scalar->r(1) << " " << _scalar->r(2) << "  "
        << std::fixed <<std::setprecision(9) << _scalar->scalar << "\n";

      _flux.precision(prec);
      _flux.setf(mode,std::ios::floatfield);
      return _flux;
    }
};



struct ScalarField
{
    int numScalares;
    std::string name;
    std::vector<Scalar> scalares;
    Vector3d r;
    ScalarField()
    {
        name = "scalar_field";
        numScalares = 0;
    }
    ScalarField(std::string _name) :
        name(_name)
    {
        numScalares = 0;
    }
    void setElement(Scalar _scalar)
    {
        scalares.push_back(_scalar);
        numScalares++;
    }
    double getMean()
    {
        double mean = 0.0;
        for (auto iScalar : scalares)
        {
            mean += iScalar.scalar;
        }
        return mean / numScalares;
    }
    void record(std::string _address)
    {
        std::string fullAddress = _address + name + ".field";
        std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
        for (auto &iScalar : scalares)
        {
            out << &iScalar;
        }
        out.close();
    }
};

}

#endif // SCALAR_H
