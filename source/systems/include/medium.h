/************************************************
 * Module: Environment.h
 * Author: Kirill A. Komarov
 * Modified: 20 Jar 2019
 * Purpose: Declaration of the class Environment
*************************************************/

#ifndef MEDIUM_H
#define MEDIUM_H

#include "mathlist.h"
#include "space.h"
#include "shape.h"
#include "object.h"
#include "materiallist.h"
#include "strength.h"
#include "yukawakernal.h"
#include "electricfield.h"

namespace tuco {

struct Environment
{    
    Environment(Material* material_);
//**Базовые функции и методы:
    void setElectricField(ph::ElectricField* field);
    void record(std::string _address, std::string _name);
    double getDebyeLength();
    ph::ElectricField* getElectricField();
    ph::GreenKernel* getCreenCore();
    Material* getMaterial();
    Space* getSpace();
private:
    double kappa_;
    std::shared_ptr<Space> space_;
    std::shared_ptr<ph::GreenKernel> green_;
    std::shared_ptr<Material> material_;
    std::shared_ptr<ph::ElectricField> field_;
};

}

#endif // MEDIUM_H
