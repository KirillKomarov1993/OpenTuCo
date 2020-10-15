#ifndef PHYSICALSTATE_H
#define PHYSICALSTATE_H

namespace tuco {

struct PhysicalState
{
    double density;
    double temperature;
    PhysicalState(double _temperature);
    PhysicalState(double _density, double _temperature);
};

}

#endif // PHYSICALSTATE_H
