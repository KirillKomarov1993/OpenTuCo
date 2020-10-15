#ifndef LATTICE_H
#define LATTICE_H

#include <memory>

#include "particle.h"
#include "bravaislattice.h"

namespace cs {

struct Lattice
{    
    Lattice(std::string _flag, BravaisLattice* _bravais, Vector3d _r);
    double getTranslation();
    bool isMainLattice();
    Vector3d getNodePosition(Vector3d _n);
    Vector3d getPosition();
    BravaisLattice* getBravaisLattice()
    {
        return bravais_;
    }
protected:
    bool flag_;
    Vector3d r_;
    BravaisLattice* bravais_;
};


/*


struct Quasistructure2 : public Structure
{
    double trn;
    double l1;
    Quasistructure2(double _trn, std::vector<Object*> _objects) :
        trn(_trn * (1.0 + sqrt(3.0))), Structure("qs2")
    {
        l1 = _trn;
        define_(_objects);
    }
private:
    void define_(std::vector<Object*> _objects)
    {
        setLattice(new Lattice("main", new Square(trn), Eigen::Vector3d(0.0, 0.0, 0.0), _objects[0]));
        setLattice(new Lattice("side1", new Square(trn), Eigen::Vector3d(l1, 0.0, 0.0), _objects[1]));
        setLattice(new Lattice("side2", new Square(trn), Eigen::Vector3d(l1 * (1.0 + sqrt(3.0) / 2.0), l1 / 2.0, 0.0), _objects[2]));
        setLattice(new Lattice("side3", new Square(trn), Eigen::Vector3d(l1 / 2.0, l1 * sqrt(3.0) / 2.0, 0.0), _objects[3]));
        setLattice(new Lattice("side4", new Square(trn), Eigen::Vector3d(l1 * (sqrt(3.0) + 1.0) / 2.0, l1 * sqrt(2), 0.0), _objects[4]));
        setLattice(new Lattice("side5", new Square(trn), Eigen::Vector3d(l1 * (sqrt(3.0) + 3.0) / 2.0, l1 * sqrt(2), 0.0), _objects[5]));
        setLattice(new Lattice("side6", new Square(trn), Eigen::Vector3d(l1 / 2.0, l1 * (1.0 + sqrt(3) / 2.0), 0.0), _objects[6]));
        setLattice(new Lattice("side7", new Square(trn), Eigen::Vector3d(l1 * (sqrt(3.0) + 2.0) / 2.0, l1 * (1.0 / 2.0 + sqrt(3)) , 0.0), _objects[7]));

    }
};

*/

}

#endif // LATTICE_H
