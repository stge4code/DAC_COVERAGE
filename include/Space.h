#ifndef SPACE_H
#define SPACE_H
#include "Point.h"
#include "Sphere.h"
#include "Rotation.h"
#include "Detector.h"
#include "DAC.h"

class Space
{
public:
    Space(int, double, Rotation);
    Space(int, double, Rotation, Sphere*);
    virtual ~Space();
    Point* getPoint(long);
    long getVolume();
    long calcChecked();
    void refreshCheckedPoints();
    void markPoints(DAC*, Detector*, Sphere*, Sphere*, double);
    void markPoints(DAC*, Detector*, Sphere*, double);
    void markPoints(Sphere*);
    void rotateSpaceForward();
    void rotateSpaceBack();
    void setRotation(Rotation rot);
protected:
private:
    Point** space = 0;
    long volume = 0;
    double unitcellparameter;
    Rotation rot;

};

#endif // SPACE_H
