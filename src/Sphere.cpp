#include <iostream>
#include <cmath>
#include "Sphere.h"


Sphere::Sphere(Point center_, double R_): center(center_), R(R_)
{

}
Sphere::~Sphere()
{
    center.~Point();
}

bool Sphere::withinSphere(Point* point_)
{
    double r = pow(point_->getX() - center.getX(), 2) + pow(point_->getY() - center.getY(), 2) + pow(point_->getZ() - center.getZ(), 2) - R * R;
    if (r <= 0) return true;
    return false;
}

bool Sphere::onSphere(Point* point_, double precise_)
{
    double r = pow(point_->getX() - center.getX(), 2) + pow(point_->getY() - center.getY(), 2) + pow(point_->getZ() - center.getZ(), 2) - R * R;
    if (r * r <  precise_ * precise_) return true;
    return false;
}


