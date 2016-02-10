#ifndef DAC_H
#define DAC_H
#include "Rotation.h"

class DAC
{
    public:
        DAC();
        DAC(double, Point, Rotation);
        virtual ~DAC();
        bool inDAC(Point*);
        void setRotation(Rotation);
        Point* getCenter();
    protected:
    private:
        double psi = 0;
        double psit = 0;
        Rotation rot;
        Point center;
};

#endif // DAC_H
