#ifndef ROTATINGELECTRICFIELD_H
#define ROTATINGELECTRICFIELD_H

#include "homogemiusfield.h"

namespace ph {

struct HomogeneousRotatingField : HomogeneousField {
    HomogeneousRotatingField(unsigned long number, Vector3d, unsigned short numIterations, double angle);
    HomogeneousRotatingField(unsigned long number, Vector3d, unsigned short numIterations1, double angle1, unsigned short numIterations2, double angle2);
    ~HomogeneousRotatingField();
    void rotateElectricFeild();
    void reset();
    bool isFinish();
protected:
    unsigned short numIterations, numIterations2;
    unsigned short nIterations1, nIterations2;
    double deltaPhi, deltaTheta;
    double angle, angle2;
    Vector3d direction0_;
    bool flag2D = false;
    bool flag3D = false;
};

}

#endif // ROTATINGELECTRICFIELD_H
