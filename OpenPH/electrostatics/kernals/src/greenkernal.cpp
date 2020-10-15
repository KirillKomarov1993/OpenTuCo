#include "greenkernal.h"

namespace ph {
    GreenKernel::GreenKernel()
    {
        system = "SGS";
        coef = 1.0;
        //setSystem();
    }
    GreenKernel::GreenKernel(std::string _system) :
        system(_system)
    {
        setSystem();
    }
    GreenKernel::~GreenKernel()
    {

    }
    void GreenKernel::setSystem()
    {
        if (system == "SGS") {
            coef = 1.0;
            //kappa = 4.0 * math::pi();
        }
        else if(system == "SI") {
            coef = 1.0 / (4 * pi() * epsilon());
            //kappa = 1.0;
        }
    }
    int GreenKernel::getIndex()
    {
        return index;
    }
}

/*
namespace ph {

GreenKernal::GreenKernal()
{
    system = "SGS";
    coef = 1.0;
    //setSystem();
}
void GreenKernal::setSystem()
{
    if (system == "SGS") {
        coef = 1.0;
        //kappa = 4.0 * math::pi();
    }
    else if(system == "SI") {
        coef = 1.0 / (4 * pi() * epsilon());
        //kappa = 1.0;
    }
}

}

*/
