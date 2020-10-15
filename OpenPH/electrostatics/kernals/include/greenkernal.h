#ifndef GREENKERNAL_H
#define GREENKERNAL_H

#include "mathlist.h"
#include "physlist.h"
//#include <mesh/polygon.h>

namespace ph {

struct GreenKernel
{
    int index;
    double coef;
    //double kappa;
    std::string name;
    std::string system;
    GreenKernel();
    GreenKernel(std::string _system);
    virtual ~GreenKernel();
    void setSystem();
    int getIndex();
    virtual double getFunction(Vector3d _P, Vector3d _Q) = 0;
    virtual bool isSimplyCore() = 0;
    virtual Vector3d getGradient(Vector3d _P, Vector3d _Q) = 0;
    virtual Matrix3d getJacobianMatrix(Vector3d _P, Vector3d _Q) = 0;
    virtual Matrix3d getDipoleOperator(Vector3d _P, Vector3d _Q) = 0;
};

}

#endif // GREENKERNAL_H
