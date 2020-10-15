#ifndef DIPOLOID_H
#define DIPOLOID_H

#include "particles/particle.h"



struct Dipoloid : Particle
{    
    Dipoloid(int _number, State* _state, Object* _object) :
        Particle(_number, "dipoloid", _state, _object)
    {
        flag = false;
        //dipole = new Dipole(number, state->r);
    }
    Dipoloid(bool _flag, int _number, State* _state, Object* _object) :
        Particle(_number, "dipoloid", _state, _object)
    {
        flag = _flag;
        //dipole = new Dipole(number, state->r);
    }
    void clear()
    {
        dipole->clear();
    }
    void setDipoleMoment(Dipole* _dipole)
    {
        dipole = _dipole;
    }
    void record(std::string _address, std::string _name)
    {

    }
    double getTotalCharge()
    {
        return 0.0;
    }
    double getAbsTotalCharge()
    {
        return 0.0;
    }
    Dipole* getDipoleMoment()
    {
        return dipole;
    }
    Scalar getElectricPotential(Vector _r)
    {
        if (dipole->r != _r)
        {
            return dipole->getPotential(_r);
        }
        else
        {
            return Scalar(0.0, _r);
        }
    }
    Strength getElectricStrength(Vector _r)
    {
        if (dipole->r != _r)
        {
            return dipole->getStrength(_r);
        }
        else
        {
            return Strength(Eigen::Vector3d(0.0, 0.0, 0.0), _r);
        }
    }
    Energy getSelfEnergy()
    {
        return Energy(pow(dipole->p.norm(), 2) / (pow(1.0, 3)) / 2.0, "electric");
    }
    Energy getExternalEnergy(HomogeneousField* _field)
    {
        return Energy(-getDipoleMoment()->p.dot(_field->strength) / 2.0, "electric");
    }
};

#endif // DIPOLOID_H
