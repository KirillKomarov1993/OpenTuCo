#include "rotatingelectricfield.h"

namespace ph {

HomogeneousRotatingField::HomogeneousRotatingField(unsigned long number, Vector3d strength, unsigned short numIterations, double angle) :
    HomogeneousField(number, strength), numIterations(numIterations), angle(angle)
{
    nIterations1 = 0;
    nIterations2 = 0;
    deltaPhi = angle / numIterations;
    deltaTheta = 0.0;
    direction0_ = direction;
    flag2D = true;
}
HomogeneousRotatingField::HomogeneousRotatingField(unsigned long number, Vector3d strength, unsigned short numIterations1, double angle1,
                                                                                            unsigned short numIterations2, double angle2) :
    HomogeneousField(number, strength), numIterations(numIterations1), angle(angle1), numIterations2(numIterations2), angle2(angle2)
{
    nIterations1 = 0;
    nIterations2 = 0;
    deltaPhi = angle / numIterations;
    deltaTheta = angle2 / numIterations2;
    direction0_ = direction;
    flag3D = true;
}
HomogeneousRotatingField::~HomogeneousRotatingField()
{

}
void HomogeneousRotatingField::rotateElectricFeild()
{
    if (flag2D) {
        direction = getRotationMatrix3D(deltaPhi, 0.0) * direction;
        nIterations1++;
    }
    if (flag3D) {
        direction = getRotationMatrix3D("z", deltaPhi) * direction;
        nIterations1++;
        if (nIterations1 >= numIterations) {
            nIterations1 = 0;
            direction = getRotationMatrix3D("y", nIterations2 * deltaTheta) * direction0_;
            nIterations2++;
            //std::cout << nIterations2 * deltaTheta << std::endl;
        }
    }

}
void HomogeneousRotatingField::reset()
{
    nIterations1 = 0;
    nIterations2 = 0;
    direction = direction0_;
}
bool HomogeneousRotatingField::isFinish()
{
    if (flag2D) {
        return nIterations1 >= numIterations;
    }
    if (flag3D) {
        return nIterations2 >= numIterations2;
    }
}
}
