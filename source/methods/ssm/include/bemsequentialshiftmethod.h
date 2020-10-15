#ifndef BEMSEQUENTIALSHIFTMETHOD_H
#define BEMSEQUENTIALSHIFTMETHOD_H

#include "tucomethod.h"
#include "sequentialshiftmethod.h"
#include "rotatingelectricfield.h"

namespace tuco {

class BEMSequentialShiftMethod : public SequentialShiftMethod
{
    ph::HomogeneousRotatingField* field;
    TuCoMethod* method;
    void computerTunableEnergy();
public:
    BEMSequentialShiftMethod(Configurator* _configuration, TunableCluster* _tunableCluster, ph::HomogeneousRotatingField* _field, TuCoMethod* _cdm);
};

}

#endif // BEMSEQUENTIALSHIFTMETHOD_H
