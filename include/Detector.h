#ifndef DETECTOR_H
#define DETECTOR_H
#include "Point.h"

class Detector
{
    public:
        Detector();
        virtual ~Detector();
        Detector(Point);
        bool inDetector(Point*, Point*);
    protected:
    private:
        Point center;
};

#endif // DETECTOR_H
