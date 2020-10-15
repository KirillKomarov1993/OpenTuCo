#include "physicalstate.h"

namespace tuco {

PhysicalState::PhysicalState(double _temperature) :
    temperature(_temperature)
{

}
PhysicalState::PhysicalState(double _density, double _temperature) :
    density(_density), temperature(_temperature)
{

}

}
