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
    for(int i = 0; i < volume; i++) (*(space + i))->~Point();
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

void Space::markPoints(DAC* dac_, Sphere* sphere_, Detector* detector_, double precise_)
{
    for(int i = 0; i < volume; i++)
    {
        if(dac_->inDAC(getPoint(i)))
        {
            if(sphere_->onSphere(getPoint(i), precise_))
            {
                if(detector_->inDetector(getPoint(i), dac_->getCenter()))
                {
                    getPoint(i)->setCheck(true);
                }
            }
        }
    }
}

/*void Space::markPoints(Sphere* const sphere_, Sphere* const resolution_){
     for(int i = 0; i < getVolume(); i++) if(sphere_->withinSpherePositive(&getPoint(i), resolution_)) getPoint(i).setCheck(true);
}
*/
