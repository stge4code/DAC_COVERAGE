#ifndef ROTATION_H
#define ROTATION_H
#include "Point.h"

class Rotation
{
public:
    Rotation();
    virtual ~Rotation();
    Rotation(double, double, double);
    void RotateForward(Point*);
    void RotateBack(Point*);
    Rotation* createInvertedRotation();
protected:
private:
    double aX = 0;
    double aY = 0;
    double aZ = 0;

    double aXc = 0;
    double aXs = 0;

    double aYc = 0;
    double aYs = 0;

    double aZc = 0;
    double aZs = 0;
};

#endif // ROTATION_H
