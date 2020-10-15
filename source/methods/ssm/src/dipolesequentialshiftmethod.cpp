#include "dipolesequentialshiftmethod.h"

namespace tuco {

void DipoleSequentialShiftMethod::computerTunableEnergy()
{
    tunableCluster->reset("energy");
    method->setInteractionsMatrix();    
    while(!field->isFinish()) {
        method->computer(field);
        tunableCluster->computerTunableEnergy();
        //tunableCluster->computerMadelungEnergy();
        field->rotateElectricFeild();
        //std::cout << std::endl;
    }
    field->reset();
    //std::cin.get();
}
DipoleSequentialShiftMethod::DipoleSequentialShiftMethod(Configurator* _configuration, TunableCluster* _tunableCluster, ph::HomogeneousRotatingField* _field, TuCoMethod* _cdm) :
    SequentialShiftMethod(_configuration, _tunableCluster)
{
    this->method = _cdm;
    this->field = _field;
}



}
