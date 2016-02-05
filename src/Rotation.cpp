#include <cmath>
#include "Matrix.h"
#include "Rotation.h"

Rotation::Rotation()
{
    //ctor
}

Rotation::Rotation(double aX_, double aY_, double aZ_): aX(aX_), aY(aY_), aZ(aZ_)
{

}

Rotation::~Rotation()
{
    //dtor
}

void Rotation::RotateForward(Point* point_){
    Matrix* mx = new Matrix(1, 0, 0, 0, cos(aX), -sin(aX), 0, sin(aX), cos(aX));
    Matrix* my = new Matrix(cos(aY), 0, sin(aY), 0, 1, 0, -sin(aY), 0, cos(aY));
    Matrix* mz = new Matrix(cos(aZ), -sin(aZ), 0, sin(aZ), cos(aZ), 0, 0, 0, 1);
    Matrix* m = new Matrix(mx, my, mz);
    m->MatrixMPoint(point_);
    delete m;
    delete mx;
    delete my;
    delete mz;
}

void Rotation::RotateBack(Point* point_){
    Matrix* mx = new Matrix(1, 0, 0, 0, cos(-aX), -sin(-aX), 0, sin(-aX), cos(-aX));
    Matrix* my = new Matrix(cos(-aY), 0, sin(-aY), 0, 1, 0, -sin(-aY), 0, cos(-aY));
    Matrix* mz = new Matrix(cos(-aZ), -sin(-aZ), 0, sin(-aZ), cos(-aZ), 0, 0, 0, 1);
    Matrix* m = new Matrix(mz, my, mx);
    m->MatrixMPoint(point_);
    delete m;
    delete mx;
    delete my;
    delete mz;
}
