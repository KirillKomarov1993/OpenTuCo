#include "selfconsistentmethod.h"


namespace tuco {

SelfConsistentMethod::SelfConsistentMethod(DipoleModel* _model) :
    model(_model)
{

}
SelfConsistentMethod::~SelfConsistentMethod()
{

}
void SelfConsistentMethod::computer(ph::ElectricField* _field)
{
    if(!flagMatrix) {
        setInteractionsMatrix();
    }
    //std::cout << "Solving of the linear system, wait..." << std::endl;
    setDipoleMoment(matrix.ldlt().solve(getColumnVector(_field)));
/*
    std::cout << "________________________________________________" << std::endl;
    std::cout << "|                                              |" << std::endl;
    std::cout << "|  The linear system was solved successfully!  |" << std::endl;
    std::cout << "|                                              |" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
*/
}
void SelfConsistentMethod::setBlock(MacroParticle* _particle1, MacroParticle* _particle2)
{
    T = model->getBlockMatrix(_particle1, _particle2);
    for (int alpha = 0; alpha < space->dim; alpha++)
    {
        for (int beta = 0; beta < space->dim; beta++)
        {
            matrix(alpha + (_particle1->getNumber() - 1) * space->dim,
                    beta + (_particle2->getNumber() - 1) * space->dim) += T(alpha, beta);
        }
    }
}

}
