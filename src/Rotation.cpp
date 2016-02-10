#include <cmath>
#include "Matrix.h"
#include "Rotation.h"

Rotation::Rotation()
{
    //ctor
}

Rotation::Rotation(double aX_, double aY_, double aZ_): aX(aX_), aY(aY_), aZ(aZ_)
{
    aXc = cos(aX_);
    aXs = sin(aX_);

    aYc = cos(aY_);
    aYs = sin(aY_);

    aZc = cos(aZ_);
    aZs = sin(aZ_);
}

Rotation* Rotation::createInvertedRotation(){
    Rotation* rot = new Rotation(-aX, -aY, -aZ);
    return rot;
}

Rotation::~Rotation()
{
    //dtor
}

void Rotation::RotateForward(Point* point_){
    Matrix* mx = new Matrix(1, 0, 0, 0, aXc, -aXs, 0, aXs, aXc);
    Matrix* my = new Matrix(aYc, 0, aYs, 0, 1, 0, -aYs, 0, aYc);
    Matrix* mz = new Matrix(aZc, -aZs, 0, aZs, aZc, 0, 0, 0, 1);
    Matrix* m = new Matrix(mx, my, mz);
    m->MatrixMPoint(point_);
    delete m;
    delete mx;
    delete my;
    delete mz;
}

void Rotation::RotateBack(Point* point_){
    Matrix* mx = new Matrix(1, 0, 0, 0, aXc, aXs, 0, -aXs, aXc);
    Matrix* my = new Matrix(aYc, 0, -aYs, 0, 1, 0, aYs, 0, aYc);
    Matrix* mz = new Matrix(aZc, aZs, 0, -aZs, aZc, 0, 0, 0, 1);
    Matrix* m = new Matrix(mz, my, mx);
    m->MatrixMPoint(point_);
    delete m;
    delete mx;
    delete my;
    delete mz;
}
