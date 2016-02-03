#include <iostream>
#include <cmath>
#include "Space.h"

Space::Space(long size_)
{
    volume = 8 * pow(size_ + 1, 3);
    space = new Point[volume];
    long index = 0;
    for(double i = -size_; i <= size_; i += 1.0)
    {
        for(double j = -size_; j <= size_; j += 1.0)
        {
            for(double k = -size_; k <= size_; k += 1.0)
            {
                *(space + index++) = Point(i / size_, j / size_, k / size_);
            }
        }
    }
}

Space::~Space()
{
    delete[] space;
}

Point& Space::getPoint(long index_)
{
    return *(space + index_);
}
long Space::getVolume()
{
    return volume;
}
long Space::calcChecked()
{
    long result = 0;
    for(long i = 0; i < getVolume(); i++) if(getPoint(i).getCheck()) result++;
    return result;
}

void Space::refreshCheckedPoints()
{
    for(long i = 0; i < getVolume(); i++) getPoint(i).setCheck(false);
}

void Space::markPoints(Sphere* const sphere_){
     for(long i = 0; i < getVolume(); i++) if(sphere_->withinShperePositive(getPoint(i))) getPoint(i).setCheck(true);
}

void Space::markPoints(Sphere* const sphere_, Sphere* const resolution_){
     for(long i = 0; i < getVolume(); i++) if(sphere_->withinShperePositive(getPoint(i), resolution_)) getPoint(i).setCheck(true);
}
