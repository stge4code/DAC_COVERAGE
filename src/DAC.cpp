#include <math.h>
#include "Rotation.h"
#include "DAC.h"

DAC::DAC()
{
    //ctor
}


DAC::DAC(double psi_, Point center_, Rotation rot_): psi(psi_), center(center_), rot(rot_)
{

}

Point* DAC::getCenter()
{
return &center;
}


DAC::~DAC()
{
    rot.~Rotation();
    center.~Point();
}

bool DAC::inDAC(Point* point_)
{
    point_->setX(point_->getX() - center.getX());
    point_->setY(point_->getY() - center.getY());
    point_->setZ(point_->getZ() - center.getZ());
    rot.RotateBack(point_);
    double x = point_->getX();
    double y = point_->getY();
    double z = point_->getZ();
    rot.RotateForward(point_);
    point_->setX(point_->getX() + center.getX());
    point_->setY(point_->getY() + center.getY());
    point_->setZ(point_->getZ() + center.getZ());
    if ((pow(y, 2) + pow(z, 2)) <= pow(x * tan(psi), 2)) return true;
    return false;
}
void DAC::setRotation(Rotation rot_)
{
    rot.~Rotation();
    rot = rot_;
};
