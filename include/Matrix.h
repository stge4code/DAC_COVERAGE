#ifndef MATRIX_H
#define MATRIX_H
#include "Point.h"


class Matrix
{
    public:
        Matrix();
        Matrix(double*);
        Matrix(double, double, double, double, double, double, double, double, double);
        Matrix(Matrix*, Matrix*, Matrix*);
        double getItem(int);
        void MatrixMPoint(Point*);
        virtual ~Matrix();
    protected:
    private:
        double* items;
};

#endif // MATRIX_H
