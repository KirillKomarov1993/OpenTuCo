#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "physlist.h"
#include "mathlist.h"
#include "physicalstate.h"

namespace tuco {

struct Material {
    double sigma;
    double epsilon;
    double kappa;
    double mu;
    double density;
    double viscosity;
    double xi_e;
    std::string name;
    std::string formula;
    std::string electricType;
    PhysicalState* physicalstate;
    Material()
    {

    }
    Material(PhysicalState* _physicalstate) :
        physicalstate(_physicalstate)
    {

    }
    Material(double _epsilon) :
        epsilon(_epsilon)
    {

    }
    Material(std::string _name, PhysicalState* _physicalstate) :
        name(_name), physicalstate(_physicalstate)
    {
        if (name == "diamond") {
            formula = "C";
            electricType = "dielectric";
            epsilon = 1.0;
            mu = 1.0;
            viscosity = 8.9e-4;  // [Pa * s]
            density = 0.0;
            setAdditional();
        }
    }
    ~Material()
    {

    }
    void setAdditional()
    {
        xi_e = (epsilon - 1.0) / (4.0 * ph::pi());
    }
    friend std::ostream& operator << (std::ostream& _flux, const Material* _material)
    {
      std::ios::fmtflags mode = _flux.flags();
      _flux.setf(std::ios::fixed,std::ios::floatfield);
      auto prec = _flux.precision(3);

      _flux
        << " Material: " << _material->name   << " (" << _material->formula << ")" << "\n"
        << "   epsilon = " << std::setw(4) <<  _material->epsilon   << "\n"
        << "   mu = " << std::setw(4) << _material->mu <<  "\n"
        << "   viscosity = " << std::setw(4) <<  _material->viscosity   << "\n"
        << "   density = " << std::setw(4) <<  _material->density   << "\n"
        << "_____________________________________________ " << "\n";

      _flux.precision(prec);
      _flux.setf(mode,std::ios::floatfield);
      return _flux;
    }
};


struct SiliconDioxide : Material
{
    SiliconDioxide()
    {
        name = "silica";
        formula = "SiO2";
        electricType = "dielectric";
        setProperties();
    }
    SiliconDioxide(PhysicalState* _physicalstate):
        Material(_physicalstate)
    {
        name = "silica";
        formula = "SiO2";
        electricType = "dielectric";
        setProperties();
    }
    void setProperties()
    {
    //! epsilon = 4.0;    // 100%
        epsilon = 2.925;  // 75 %
        //epsilon = 2000.925;  // 75 %
        mu = 1.0;
        viscosity = 8.9e-4;  // [Pa * s]
        //density = 2.648 * g() / pow(sm(), 3);
        density = 2.648;
        setAdditional();
    }
};

struct Water : Material
{
    Water()
    {
        name = "water";
        formula = "H2O";
        electricType = "dielectric";
        setProperties();
    }
    Water(PhysicalState* _physicalstate) :
        Material(_physicalstate)
    {
        name = "water";
        formula = "H2O";
        electricType = "dielectric";
        setProperties();
    }
    void setProperties()
    {
        epsilon = 80.1;  // T = 20 C;
        mu = 1.0;
        viscosity = 8.9e-4;  // [Pa * s]
        density = 998; // [kg / m3]
        kappa = 0.0;
        setAdditional();
    }
};

struct Ethanol : Material
{
    Ethanol()
    {
        name = "ethanol";
        formula = "C2H6O";
        electricType = "dielectric";
        setProperties();
    }
    Ethanol(PhysicalState* _physicalstate) :
        Material(_physicalstate)
    {
        name = "ethanol";
        formula = "C2H6O";
        electricType = "dielectric";
        setProperties();
    }
    void setProperties()
    {
        //epsilon = 24.3;  //!Найти справочник;
        epsilon = 0.1;
        mu = 1.0;
        viscosity = 8.9e-4;  // [Pa * s]
        density = 789; // [kg / m3]
        setAdditional();
    }
};

struct Cyclohexane : Material
{
    Cyclohexane()
    {
        name = "cyclohexane";
        formula = "Cy";
        electricType = "dielectric";
        setProperties();
    }
    Cyclohexane(PhysicalState* _physicalstate) :
        Material(_physicalstate)
    {
        name = "cyclohexane";
        formula = "Cy";
        electricType = "dielectric";
        setProperties();
    }
    void setProperties()
    {
        epsilon = 0.3;
        mu = 1.0; //!Найти справочник;
        viscosity = 1.02; // [cP]
        density = 778.1;  // [kg / m3]
        setAdditional();
    }
};

struct Plexiglas : Material
{
    Plexiglas()
    {
        name = "poly(methyl methacrylate)";
        formula = "PMMA";
        electricType = "dielectric";
        setProperties();
    }
    Plexiglas(PhysicalState* _physicalstate) :
        Material(_physicalstate)
    {
        name = "poly(methyl methacrylate)";
        formula = "PMMA";
        electricType = "dielectric";
        setProperties();
    }
    void setProperties()
    {
        epsilon = 1.0;
        mu = 1.0; //!Найти справочник;
        viscosity = 1.0; //!Найти справочник;
        density = 1180;  // [kg / m3]
        setAdditional();
    }
};

struct Polystyrene : Material
{
    Polystyrene(PhysicalState* _physicalstate) :
        Material(_physicalstate)
    {
        name = "polystyrene";
        formula = "PS";
        electricType = "dielectric";
        setProperties();
    }
    void setProperties()
    {
        epsilon = 2.5;
        mu = 1.0; //!Найти справочник;
        viscosity = 1.0; //!Найти справочник;
        density = 1000;  // [kg / m3]
        setAdditional();
    }
};

struct Vacuum : Material
{
    Vacuum()
    {
        name = "vacuum";
        formula == "-";
        electricType = "dielectric";
        setProperties();
    }
    Vacuum(PhysicalState* _physicalstate):
        Material(_physicalstate)
    {
        name = "vacuum";
        formula == "-";
        setProperties();
    }
    void setProperties()
    {
        epsilon = 1.0;
        mu = 1.0;
        viscosity = 8.9e-4;  // [Pa * s]
        density = 0.0;
        setAdditional();
    }
};

struct Carbon : Material
{
    Carbon()
    {
        name = "carbone";
        formula == "C";
        electricType = "metal";
        setProperties();
    }
    Carbon(PhysicalState* _physicalstate):
        Material(_physicalstate)
    {
        name = "carbone";
        formula == "C";
        electricType = "metal";
        setProperties();
    }
    void setProperties()
    {
        sigma = 1e5;  // [Sm]
        epsilon = 1e3;
        //mu = 1.0;
        viscosity = 8.9e-4;  // [Pa * s]
        density = 0.0;
        setAdditional();
    }
};

struct Cuprume : Material
{
    Cuprume(PhysicalState* _physicalstate):
        Material(_physicalstate)
    {
        name = "cuprume";
        formula == "Cu";
        electricType = "metal";
        setProperties();
    }
    void setProperties()
    {
        sigma = 1e5;  // [Sm]
        //epsilon = ;
        //mu = 1.0;
        viscosity = 8.9e-4;  // [Pa * s]
        density = 0.0;
        setAdditional();
    }
};

}

#endif // MATERIAL_H
