#include "bemsequentialshiftmethod.h"

namespace tuco {

void BEMSequentialShiftMethod::computerTunableEnergy()
{
    tunableCluster->reset("energy");
    method->setInteractionsMatrix();
    while(!field->isFinish()) {
        method->computer(field);
        //std::cout << tunableCluster->getMacroParticle(1)->getDipole()->getValue()  << std::endl;
        //std::cout << tunableCluster->getMacroParticle(1)->getSelfEnergy().getValue() << std::endl;
        //tunableCluster->record("");
        //std::cin.get();
        tunableCluster->computerTunableEnergy();
        //tunableCluster->computerMadelungEnergy();
        field->rotateElectricFeild();
    }
    field->reset();
}

BEMSequentialShiftMethod::BEMSequentialShiftMethod(Configurator* _configuration, TunableCluster* _tunableCluster, ph::HomogeneousRotatingField* _field, TuCoMethod* _cdm) :
    SequentialShiftMethod(_configuration ,_tunableCluster)
{
    this->method = _cdm;
    this->field = _field;
}


}
