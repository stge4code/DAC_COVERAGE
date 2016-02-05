#include <iostream>
#include <cmath>
#include "Space.h"
#include "Sphere.h"
#include "Detector.h"
#include "DAC.h"

Space::Space(int size_, double unitcellparameter_, Rotation rot_)
{
    rot = rot_;
    volume = pow(2 * size_ + 1, 3);
    unitcellparameter = unitcellparameter_;
    space = new Point*[volume];
    int index = 0;
    for(int i = -size_; i <= size_; i++)
    {
        for(int j = -size_; j <= size_; j++)
        {
            for(int k = -size_; k <= size_; k++)
            {
                *(space + index++) = new Point(i / unitcellparameter_, j / unitcellparameter_, k / unitcellparameter_);
            }
        }
    }
}

Space::~Space()
{
    rot.~Rotation();
    for(int i = 0; i < volume; i++) delete *(space + i);
    delete[] space;
}


void Space::setRotation(Rotation rot_)
{
    rot.~Rotation();
    rot = rot_;
}

void Space::rotateSpace()
{
    for(int i = 0; i < volume; i++) rot.RotateForward(getPoint(i));
}

Point* Space::getPoint(int index_)
{
    return (*(space + index_));
}
int Space::getVolume()
{
    return volume;
}
int Space::calcChecked()
{
    int result = 0;
    for(int i = 0; i < volume; i++) if(getPoint(i)->getCheck()) result++;
    return result;
}

void Space::refreshCheckedPoints()
{
    for(int i = 0; i < volume; i++) getPoint(i)->setCheck(false);
}

void Space::markPoints(DAC* dac_,  Detector* detector_, Sphere* sphere_resolution_, Sphere* sphere_ewald_, double precise_)
{
    for(int i = 0; i < volume; i++)
    {
        Point* point = getPoint(i);
        if(!point->getCheck())
        {
            if(sphere_resolution_->withinSphere(point))
            {
                if(dac_->inDAC(point))
                {
                    if(sphere_ewald_->onSphere(point, precise_))
                    {
                        if(detector_->inDetector(point, dac_->getCenter()))
                        {
                            point->setCheck(true);
                        }
                    }
                }
            }
        }
    }
}
void Space::markPoints(Sphere* sphere_resolution_)
{
    for(int i = 0; i < volume; i++)
    {
        Point* point = getPoint(i);

        if(sphere_resolution_->withinSphere(point))
        {

            point->setCheck(true);

        }
    }

}

/*void Space::markPoints(Sphere* const sphere_, Sphere* const resolution_){
     for(int i = 0; i < getVolume(); i++) if(sphere_->withinSpherePositive(&getPoint(i), resolution_)) getPoint(i).setCheck(true);
}
*/
