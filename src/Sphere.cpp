#include <iostream>
#include <cmath>
#include "Sphere.h"


Sphere::Sphere(Point center_, double R_): center(center_), R(R_)
{

}
Sphere::~Sphere() {}

bool Sphere::withinSphere(Point* point_)
{
    double r = pow(point_->getX() - center.getX(), 2) + pow(point_->getY() - center.getY(), 2) + pow(point_->getZ() - center.getZ(), 2);
    if ((std::abs(r - pow(R, 2)) <=  0) && (point_->getZ() >= 0)) return true;
    return false;
}

bool Sphere::onSphere(Point* point_, double precise_)
{
    double r = pow(point_->getX() - center.getX(), 2) + pow(point_->getY() - center.getY(), 2) + pow(point_->getZ() - center.getZ(), 2);
    if ((std::abs(r - pow(R, 2)) <  precise_)) return true;
    return false;
}


