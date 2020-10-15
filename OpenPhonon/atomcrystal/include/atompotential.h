#ifndef ATOMPOTENTIAL_H
#define ATOMPOTENTIAL_H

#include "mathlist.h"

namespace atom {

class Potential
{
    double norm_;
public:
    double epsilon;
    double length;
    std::string name;
    Potential()
    {

    }
    Potential(double _epsilon, double _length) :
        epsilon(_epsilon), length(_length)
    {

    }
    virtual ~Potential()
    {

    }
    virtual double getFunction(double) = 0;
    virtual double getRadialDirivate(double) = 0;
    virtual double get2RadialDirivate(double) = 0;
    virtual double get3RadialDirivate(double) = 0;
    double get2Dirivate(int alpha, int beta, VectorXd _r)
    {
        norm_ = _r.norm();
        return (get2RadialDirivate(norm_) - getRadialDirivate(norm_) / norm_)*(_r(alpha)*_r(beta) / (norm_*norm_))
                                                        + getRadialDirivate(norm_) / norm_ * ph::kronecker(alpha, beta);
    }
};

struct LennardJones : public Potential
{
    LennardJones(double _epsilon, double _length) :
        Potential(_epsilon, _length)
    {
        name = "lennard-jones";
    }
    double getFunction(double _r)
    {
        return 4.0 * epsilon * (pow(length/_r, 12) - pow(length/_r, 6));
    }
    double getRadialDirivate(double _r)
    {
        return -4.0 * epsilon / length * (12.0 * pow(length/_r, 13) - 6.0 * pow(length/_r, 7));
    }
    double get2RadialDirivate(double _r)
    {
        return 4.0 * epsilon / length / length * (12.0 * 13.0 * pow(length/_r, 14) - 6.0 * 7.0 * pow(length/_r, 8));
    }
    double get3RadialDirivate(double _r)
    {
        return -4.0 * epsilon / length / length / length * (12.0 * 13.0 * 14.0 * pow(length/_r, 15) - 6.0 * 7.0 * 8.0 * pow(length/_r, 9));
    }
};

struct Yukawa : public Potential
{
    Yukawa() :
        Potential()
    {
        name = "yukawa";
    }
    double getFunction(double _r)
    {
        return (epsilon * length) * exp(-_r / length) / _r;
    }
    double getRadialDirivate()
    {

    }
};

}

#endif // ATOMPOTENTIAL_H
