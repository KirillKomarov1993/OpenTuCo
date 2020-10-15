#include "energyelementmethod.h"

namespace tuco {

EnergyElementMethod::EnergyElementMethod(SurfaceEnergyEquation* _equation)
{
    equation.reset(_equation);
    coef = _equation->getEquationsSize();
}
EnergyElementMethod::~EnergyElementMethod()
{
}
EnergyElementMethod::EnergyElementMethod(SurfaceEnergyEquation* _equation, Environment* _medium)
{
    equation.reset(_equation);
    coef = _equation->getEquationsSize();
    equation->setEnvironment(_medium);
}
void EnergyElementMethod::computer(ph::ElectricField* _field)
{    
    std::cout << "  Predictor:  " << std::endl;
    equation->setDensityMatrix(nullDensityMatrix);
    setInteractionsMatrix();
    setColumnVector(_field);
    std::cout << "Solving of the linear system, wait..." << std::endl;
    unknowns = matrix.colPivHouseholderQr().solve(value);
    std::cout << "The linear system was solved successfully!" << std::endl;
/*
    std::cout << "  Corrector:  " << std::endl;
    computerDensityMatrix(&EnergyElementMethod::setDashDensityBlock);
    equation->setDensityMatrix(dashDensityMatrix);
    setInteractionsMatrix();
    setColumnVector(_field);
    std::cout << "Solving of the linear system, wait..." << std::endl;
    unknowns = matrix.colPivHouseholderQr().solve(value);
    std::cout << "The linear system was solved successfully!" << std::endl;
*/
    setElementEnergis();

/*
    std::cout << "________________________________________________" << std::endl;
    std::cout << "|                                              |" << std::endl;
    std::cout << "|  The linear system was solved successfully!  |" << std::endl;
    std::cout << "|                                              |" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
*/
}

}

