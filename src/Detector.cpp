#include "Point.h"
#include "Detector.h"

Detector::Detector()
{
    //ctor
}

Detector::~Detector()
{
    center.~Point();
}

Detector::Detector(Point center_):center(center_)
{
    //ctor
}

bool Detector::inDetector(Point* point_, Point* dacCenter_)
{
    double r = (point_->getX() - dacCenter_->getX()) * center.getX() + (point_->getY() - dacCenter_->getY()) * center.getY() + (point_->getZ() - dacCenter_->getZ()) * center.getZ() ;
    if (r > 0) return true;
    return false;
}
