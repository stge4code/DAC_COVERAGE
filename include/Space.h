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
    virtual ~Space();
    Point* getPoint(int);
    int getVolume();
    int calcChecked();
    void refreshCheckedPoints();
    void markPoints(DAC*, Sphere*, Detector*, double);
    void rotateSpace();
    void setRotation(Rotation rot);
protected:
private:
    Point** space = 0;
    int volume = 0;
    double unitcellparameter;
    Rotation rot;

};

#endif // SPACE_H
