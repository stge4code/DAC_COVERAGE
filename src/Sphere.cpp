#include "Sphere.h"
#include <cmath>

Sphere::Sphere(Point center_, double R_): center(center_), R(R_)
{
    Rxy = sqrt(pow(center_.getX(), 2) + pow(center_.getY(), 2));
}
Sphere::~Sphere() {}

bool Sphere::withinShperePositive(const Point& point_)
{
    double r = pow(point_.getX() - center.getX(), 2) + pow(point_.getY() - center.getY(), 2) + pow(point_.getZ() - center.getZ(), 2);
    if ((r <= pow(R, 2)) && (point_.getZ() >= 0)) return true;
    return false;
}

bool Sphere::withinShperePositive(const Point& point_, Sphere* const resolution_)
{
    if(resolution_->withinShperePositive(point_)){
    double r = pow(point_.getX() - center.getX(), 2) + pow(point_.getY() - center.getY(), 2) + pow(point_.getZ() - center.getZ(), 2);
    if ((r <= pow(R, 2)) && (point_.getZ() >= 0)) return true;
    }
    return false;
}

void Sphere::moveCenter(double phi_)
{
    center.setX(Rxy * cos(phi_));
    center.setY(Rxy * sin(phi_));
}
