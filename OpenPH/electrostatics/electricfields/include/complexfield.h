#ifndef EXTERNALFILED_H
#define EXTERNALFILED_H


#include "mathlist.h"
#include "math/strength.h"
#include "math/scalar.h"
//#include "electrostatics/greenkernal.h"
#include "space/symmetry.h"


// Realization:
struct HomogeneousField
{
    int number;
    Vector n;
    Vector strength;
    HomogeneousField(int _number, Vector _strength) :
        number(_number), strength(_strength)
    {

    }
    Scalar getElectricPotential(Vector _r)
    {
        return Scalar(-strength.dot(_r), _r);
    }
    Scalar getElectricPotential(Vector _r, Vector _r0)
    {
        return Scalar(-strength.dot(_r - _r0), _r);
    }
    Strength getElectricField(Vector _r)
    {
        return Strength(strength, _r);
    }
};


// Interface:
struct ExternalField
{
    std::string type;
    std::vector<HomogeneousField> hFields;
    virtual void setExternalFields() = 0;
    virtual void record(std::string _address, std::string _name) = 0;
};


/*
struct DirectedFieldN : public ExternalFieldN {
    HomogeneousFieldN* field;
    DirectedFieldN(Vector _strength)
    {
        field = new HomogeneousFieldN(0, _strength);
        type = "directed";
    }
    ~DirectedFieldN()
    {
        delete field;
    }
    void setExternalFields() = 0;
    void record(std::string _address, std::string _name)
    {
        std::string fullAdress = _address + _name + ".dirfield";
        std::ofstream out(fullAdress, std::ios::out | std::ios::binary);
        out << field->strength << "\n";
        out.close();
    }
    Scalar getElectricPotential(Vector _r)
    {
        return Scalar(-strength.dot(_r), _r);
    }
    Strength getElectricField(Vector _r)
    {
        return Strength(strength, _r);
    }
};
*/


// Realization:
struct RotatingField : public ExternalField
{
    int numFields;
    double magnetude;
    RotatingField(int _numFields, double _magnetude) :
        numFields(_numFields), magnetude(_magnetude)
    {
        type = "rotating";
    }
    RotatingField(int _numFields, double _magnetude, Symmetry* _symmetry, double _shift, double _theta) :
        numFields(_numFields), magnetude(_magnetude), symmetry(_symmetry), shift_(_shift), theta_(_theta)
    {

    }
    void setExternalFields();
    void record(std::string _address, std::string _name);
protected:
    double phi_;
    double omega_;
    double theta_;
    Eigen::Vector3d vector_;
private:
    double shift_;
    Symmetry* symmetry;
};


// Realization:
struct RhodoneaField : private RotatingField
{
    RhodoneaField(int _numFields, double _magnetude, double _coef) :
        RotatingField(_numFields, _magnetude), coef_(_coef)
    {
        type = "rhodonea";
    }
    void setExternalFields()
    {
        omega_ = math::pi() / ((double)numFields);
        int nField = 0;
        for (int i = 0; i < numFields; i++)
        {
            phi_ = i * omega_;
            vector_ << pow(sin(coef_ * phi_), 7) * cos(phi_), pow(sin(coef_ * phi_), 7) * sin(phi_), 0.0;
            hFields.push_back(HomogeneousField(nField + 1, magnetude * vector_));
            nField++;
        }
        numFields = nField;
    }
private:
    double coef_;
};


#endif // EXTERNALFILED_H
