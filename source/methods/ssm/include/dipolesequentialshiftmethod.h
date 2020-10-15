#ifndef DIPOLESEQUENTIALSHIFTMETHOD_H
#define DIPOLESEQUENTIALSHIFTMETHOD_H

#include "tucomethod.h"
#include "sequentialshiftmethod.h"
#include "rotatingelectricfield.h"

namespace tuco {

class DipoleSequentialShiftMethod : public SequentialShiftMethod
{
    ph::HomogeneousRotatingField* field;
    TuCoMethod* method;
    void computerTunableEnergy();
public:
    DipoleSequentialShiftMethod(Configurator* _configuration, TunableCluster* _tunableCluster, ph::HomogeneousRotatingField* _field, TuCoMethod* _cdm);
};

}


#endif // DIPOLESEQUENTIALSHIFTMETHOD_H
