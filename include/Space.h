#include "Point.h"
#include "Sphere.h"
#ifndef SPACE_H
#define SPACE_H


class Space
{
public:
    Space(long);
    virtual ~Space();
    Point& getPoint(long);
    long getVolume();
    long calcChecked();
    void refreshCheckedPoints();
    void markPoints(Sphere* const);
    void markPoints(Sphere* const, Sphere* const);
protected:
private:
    Point* space = 0;
    long volume = 0;

};

#endif // SPACE_H
