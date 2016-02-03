#include "Point.h"
#ifndef SPHERE_H
#define SPHERE_H


class Sphere
{
public:
    Sphere(Point, double);
    virtual ~Sphere();
    bool withinShperePositive(const Point&);
    bool withinShperePositive(const Point&, Sphere* const);
    void moveCenter(double);
protected:
private:
    Point center;
    double R = 0;
    double Rxy = 0;
};

#endif // SPHERE_H
