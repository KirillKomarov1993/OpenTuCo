#include "boundaryelementmethod.h"

namespace tuco {

BoundaryElementMethod::BoundaryElementMethod(IntegralEquation* _equation)
{
    shellEquation.reset(_equation);
    coef1 = _equation->getEquationsSize();
}
BoundaryElementMethod::~BoundaryElementMethod()
{
}
BoundaryElementMethod::BoundaryElementMethod(IntegralEquation* _equation, Environment* _medium)
{
    shellEquation.reset(_equation);
    coef1 = _equation->getEquationsSize();
    shellEquation->setEnvironment(_medium);
}
BoundaryElementMethod::BoundaryElementMethod(IntegralEquation* _shellEquation, IntegralEquation* _coreEquation, Environment* _medium)
{
    shellEquation.reset(_shellEquation);
    coreEquation.reset(_coreEquation);
    coef1 = _shellEquation->getEquationsSize();
    shellEquation->setEnvironment(_medium);
    coreEquation->setEnvironment(_medium);
}
void BoundaryElementMethod::computer(ph::ElectricField* _field)
{
    if(!flagMatrix) {
        setInteractionsMatrix();
    }
    std::cout << "Solving of the linear system, wait..." << std::endl;
    setColumnVector(_field);
    //Eigen::BiCGSTAB<Eigen::SparseMatrix<double> > solver;
    //solver.compute(matrix);
    //setSurfaceMultipoles(solver.solve(value));
    setSurfaceMultipoles(matrix.colPivHouseholderQr().solve(value));
    //setSurfaceMultipoles(value);
    //setSurfaceMultipoles(matrix.fullPivHouseholderQr().solve(value));
    std::cout << "________________________________________________" << std::endl;
    std::cout << "|                                              |" << std::endl;
    std::cout << "|  The linear system was solved successfully!  |" << std::endl;
    std::cout << "|                                              |" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
}

}

