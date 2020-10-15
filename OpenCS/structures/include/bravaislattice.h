#ifndef BRAVAISLATTICE_H
#define BRAVAISLATTICE_H

//#include "mathlist.h"
#include "reciprocallattice.h"

namespace cs {

struct Space
{
    int dim;
    std::string system;
    std::vector<VectorXd> e;
    Space(int _dim) :
        dim(_dim)
    {

    }
    Space(int _dim, std::string _system) :
        dim(_dim), system(_system)
    {
        if (system == "cartesian") {
            MatrixXd I = MatrixXd::Identity(dim, dim);
            for (int i = 0; i < dim; i++)
            {
                e.push_back(I.row(i));
            }
        }
    }
};


//! Interface:
struct BravaisLattice
{    
    BravaisLattice()
    {
        space_ = new Space(3, "cartesian");
        //setReciprocalLattice();
    }
    void setReciprocalLattice()
    {
        reciprocalLattice_ = new ReciprocalLattice(basis_);
    }
    double getVolume()
    {
        return volume_;
    }
    double getTranslation()
    {
        return trn_;
    }
    Basis* getBasis()
    {
        return basis_;
    }
    ReciprocalLattice* getReciprocalLattice()
    {
        return reciprocalLattice_;
    }
    Vector3d getCriticalPoint(std::string _pointName)
    {
        return criticalPointMap_[_pointName];
    }
    virtual void setCriticalPoints() = 0;
protected:
    double trn_;
    double volume_;
    std::string family_;
    std::string type_;
    Space* space_;
    Basis* basis_;
    ReciprocalLattice* reciprocalLattice_;
    std::map<std::string, Vector3d> criticalPointMap_;
};


struct Hexagonal : BravaisLattice
{
    Hexagonal(double _trn) :
        BravaisLattice()
    {
        trn_ = _trn;
        family_ = "h";
        type_ = "P";
        basis_= new Basis(trn_ * (space_->e[0]),
                         trn_ * (-0.5 * space_->e[0] - sqrt(3.0) / 2.0 * space_->e[1]));
        volume_ = pow(trn_, 2) * sqrt(3.0) / 4.0;
        setReciprocalLattice();
        setCriticalPoints();
    }
    void setCriticalPoints()
    {
        criticalPointMap_.insert(std::make_pair("G",  0.0 * reciprocalLattice_->getBasis()->getBasisVector(1) +
                                                      0.0 * reciprocalLattice_->getBasis()->getBasisVector(2)));
        criticalPointMap_.insert(std::make_pair("K",  2.0 / 3.0 * reciprocalLattice_->getBasis()->getBasisVector(1) +
                                                      1.0 / 3.0 * reciprocalLattice_->getBasis()->getBasisVector(2)));
        criticalPointMap_.insert(std::make_pair("M",  1.0 / 2.0 * reciprocalLattice_->getBasis()->getBasisVector(1) +
                                                      0.0 * reciprocalLattice_->getBasis()->getBasisVector(2)));
    }
};


struct Square : BravaisLattice
{
    Square(double _trn) :
        BravaisLattice()
    {
        trn_ = _trn;
        family_ = "s";
        type_ = "P";
        basis_= new Basis(trn_ * (space_->e[0]),
                         trn_ * (space_->e[1]));
        volume_ = pow(trn_, 2);
        setReciprocalLattice();
    }
    void setCriticalPoints()
    {
        criticalPointMap_.insert(std::make_pair("G", Vector3d(0.0, 0.0, 0.0)));
        criticalPointMap_.insert(std::make_pair("M", Vector3d(1.0 / 2.0, 0.0, 0.0)));
    }
};

struct Rhombic : BravaisLattice
{
    Rhombic(double _trn) :
        BravaisLattice()
    {
        trn_ = _trn;
        family_ = "r";
        type_ = "P";
        basis_= new Basis(trn_ * (space_->e[0]),
                         trn_ * (space_->e[1]));
        volume_ = pow(trn_, 2) * 3.0 / 4.0;
    }
    void setCriticalPoints()
    {

    }
};

}

/*
struct Chain : BravaisLattice
{
    Chain(Space* _space, double _density) :
        BravaisLattice(_space)
    {
        trn = getTranslation(_density);
        family = "ch";
        type = "P";
        basis= new Basis(trn * (space->e[0]));
        basis->vol = trn;
        setPoint();
    }
    void setPoint()
    {
        points.insert(std::make_pair("G", (basis->b[0])*0.0));
        points.insert(std::make_pair("M", (basis->b[0])*0.5));
    }
    double getTranslation(double _density)
    {
        if (space->dim == 1) {
            return 1.0/_density;
        }
    }

private:
    Vector r_;
};
*/


#endif // BRAVAISLATTICE_H
