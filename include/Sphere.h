#include "Point.h"
#ifndef SPHERE_H
#define SPHERE_H


class Sphere
{
public:
    Sphere(Point, double);
    virtual ~Sphere();
    bool onSphere(Point*,  double );
    bool withinSphere(Point*);
protected:
private:
    Point center;
    double R = 0;
};

#endif // SPHERE_H
