#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "mathlist.h"

namespace tuco {

struct Configurator
{    
    Configurator(std::string _name);
    virtual ~Configurator();
    unsigned long getParticleCount();
    Vector3d getCoordinate(int _nNode);
    virtual void setConfiguration() = 0;
protected:
    unsigned long numParticles;
    std::string name_;
    std::string type;
    std::vector<Vector3d> basis;
    std::vector<Vector3d> coor;
    void setBasis()
    {
        if (type == "hex")
        {
            basis.resize(7);
            basis[0] << 0.0, 0.0, 0.0;
            basis[1] << 1.0, 0.0, 0.0;
            basis[2] << cos(M_PI / 3.0),  sin(M_PI / 3.0), 0.0;
            basis[3] << -cos(M_PI / 3.0),  sin(M_PI / 3.0), 0.0;
            basis[4] << -1.0, 0.0, 0.0;
            basis[5] << -cos(M_PI / 3.0),  -sin(M_PI / 3.0), 0.0;
            basis[6] <<  cos(M_PI / 3.0),  -sin(M_PI / 3.0), 0.0;
        }
        else if (type == "c")
        {
            basis.resize(9);
            basis[0] << 0.0, 0.0, 0.0;
            basis[1] << 1.0, 0.0, 0.0;
            basis[2] << 1.0, 1.0, 0.0;
            basis[3] << 0.0, 1.0, 0.0;
            basis[4] << -1.0, 1.0, 0.0;
            basis[5] << -1.0, 0.0, 0.0;
            basis[6] << -1.0, -1.0, 0.0;
            basis[7] << 0.0, -1.0, 0.0;
            basis[8] << 1.0, -1.0, 0.0;
        }
    }

};

struct Pair : Configurator
{
    Pair(std::string _name);
    void setConfiguration()
    {
        if (name_ == "P1") {
            type = "hex";
            setBasis();
            coor.resize(3);
            coor[0] = basis[0];
            coor[1] = basis[1];
            numParticles = 2;
        }
        if (name_ == "P2") {
            type = "hex";
            setBasis();
            coor.resize(3);
            coor[0] = 2.0 * basis[0];
            coor[1] = 2.0 * basis[1];
            numParticles = 2;
        }
    }
};

struct Triplets : Configurator
{
    Triplets(std::string _name);
    void setConfiguration()
    {
        if (name_ == "T1")
        {
            type = "hex";
            setBasis();
            coor.resize(3);
            coor[0] = basis[0];
            coor[1] = basis[1];
            coor[2] = basis[4];
            numParticles = 3;
        }
        else if (name_ == "T2")
        {
            type = "hex";
            setBasis();
            coor.resize(3);
            coor[0] = basis[0];
            coor[1] = basis[1];
            coor[2] = basis[2];
            numParticles = 3;
        }
        else if (name_ == "T3")
        {
            type = "c";
            setBasis();
            coor.resize(3);
            coor[0] = basis[0];
            coor[1] = basis[1];
            coor[2] = basis[3];
            numParticles = 3;
        }
        else if (name_ == "T4")
        {
            type = "hex";
            setBasis();
            coor.resize(3);
            coor[0] = basis[0];
            coor[1] = basis[1];
            coor[2] = basis[3];
            numParticles = 3;
        }
        else if (name_ == "T5")
        {
            type = "c";
            setBasis();
            coor.resize(3);
            coor[0] = basis[1];
            coor[1] = basis[3];
            coor[2] = basis[5];
            numParticles = 3;
        }
        else if (name_ == "T6")
        {
            type = "hex";
            setBasis();
            coor.resize(3);
            coor[0] = basis[1];
            coor[1] = basis[4];
            coor[2] = basis[5];
            numParticles = 3;
        }
        else if (name_ == "T7")
        {
            type = "hex";
            setBasis();
            coor.resize(3);
            coor[0] = basis[1];
            coor[1] = basis[3];
            coor[2] = basis[5];
            numParticles = 3;
        }
    }
};

}

#endif // CONFIGURATION_H
