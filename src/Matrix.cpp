#include "Point.h"
#include "Matrix.h"
#include <iostream>

Matrix::Matrix()
{
    //ctor
}

Matrix::Matrix(double* items_)
{
    items = new double[9];
    for(int i = 0; i < 9; i++){
        *(items + i) = *(items_ + i);
    }
}

Matrix::Matrix(double i11_, double i12_, double i13_, double i21_, double i22_, double i23_, double i31_, double i32_, double i33_)
{
    items = new double[9];
    int i = 0;
    *(items + i++) = i11_;
    *(items + i++) = i12_;
    *(items + i++) = i13_;
    *(items + i++) = i21_;
    *(items + i++) = i22_;
    *(items + i++) = i23_;
    *(items + i++) = i31_;
    *(items + i++) = i32_;
    *(items + i++) = i33_;
}

Matrix::~Matrix()
{
    delete[] items;
}

double Matrix::getItem(int index_){
    return *(items + index_);
};

Matrix::Matrix(Matrix* m1_, Matrix* m2_, Matrix* m3_)
{
    double* items_tmp = new double[9];
    items = new double[9];
    int i = 0;
    *(items_tmp + i++) = (*(m1_->items + 0)) * (*(m2_->items + 0)) + (*(m1_->items + 1)) * (*(m2_->items + 3)) + (*(m1_->items + 2)) * (*(m2_->items + 6));
    *(items_tmp + i++) = (*(m1_->items + 0)) * (*(m2_->items + 1)) + (*(m1_->items + 1)) * (*(m2_->items + 4)) + (*(m1_->items + 2)) * (*(m2_->items + 7));
    *(items_tmp + i++) = (*(m1_->items + 0)) * (*(m2_->items + 2)) + (*(m1_->items + 1)) * (*(m2_->items + 5)) + (*(m1_->items + 2)) * (*(m2_->items + 8));

    *(items_tmp + i++) = (*(m1_->items + 3)) * (*(m2_->items + 0)) + (*(m1_->items + 4)) * (*(m2_->items + 3)) + (*(m1_->items + 5)) * (*(m2_->items + 6));
    *(items_tmp + i++) = (*(m1_->items + 3)) * (*(m2_->items + 1)) + (*(m1_->items + 4)) * (*(m2_->items + 4)) + (*(m1_->items + 5)) * (*(m2_->items + 7));
    *(items_tmp + i++) = (*(m1_->items + 3)) * (*(m2_->items + 2)) + (*(m1_->items + 4)) * (*(m2_->items + 5)) + (*(m1_->items + 5)) * (*(m2_->items + 8));

    *(items_tmp + i++) = (*(m1_->items + 6)) * (*(m2_->items + 0)) + (*(m1_->items + 7)) * (*(m2_->items + 3)) + (*(m1_->items + 8)) * (*(m2_->items + 6));
    *(items_tmp + i++) = (*(m1_->items + 6)) * (*(m2_->items + 1)) + (*(m1_->items + 7)) * (*(m2_->items + 4)) + (*(m1_->items + 8)) * (*(m2_->items + 7));
    *(items_tmp + i++) = (*(m1_->items + 6)) * (*(m2_->items + 2)) + (*(m1_->items + 7)) * (*(m2_->items + 5)) + (*(m1_->items + 8)) * (*(m2_->items + 8));

    i = 0;
    *(items + i++) = (*(items_tmp + 0)) * (*(m3_->items + 0)) + (*(items_tmp + 1)) * (*(m3_->items + 3)) + (*(items_tmp + 2)) * (*(m3_->items + 6));
    *(items + i++) = (*(items_tmp + 0)) * (*(m3_->items + 1)) + (*(items_tmp + 1)) * (*(m3_->items + 4)) + (*(items_tmp + 2)) * (*(m3_->items + 7));
    *(items + i++) = (*(items_tmp + 0)) * (*(m3_->items + 2)) + (*(items_tmp + 1)) * (*(m3_->items + 5)) + (*(items_tmp + 2)) * (*(m3_->items + 8));

    *(items + i++) = (*(items_tmp + 3)) * (*(m3_->items + 0)) + (*(items_tmp + 4)) * (*(m3_->items + 3)) + (*(items_tmp + 5)) * (*(m3_->items + 6));
    *(items + i++) = (*(items_tmp + 3)) * (*(m3_->items + 1)) + (*(items_tmp + 4)) * (*(m3_->items + 4)) + (*(items_tmp + 5)) * (*(m3_->items + 7));
    *(items + i++) = (*(items_tmp + 3)) * (*(m3_->items + 2)) + (*(items_tmp + 4)) * (*(m3_->items + 5)) + (*(items_tmp + 5)) * (*(m3_->items + 8));

    *(items + i++) = (*(items_tmp + 6)) * (*(m3_->items + 0)) + (*(items_tmp + 7)) * (*(m3_->items + 3)) + (*(items_tmp + 8)) * (*(m3_->items + 6));
    *(items + i++) = (*(items_tmp + 6)) * (*(m3_->items + 1)) + (*(items_tmp + 7)) * (*(m3_->items + 4)) + (*(items_tmp + 8)) * (*(m3_->items + 7));
    *(items + i++) = (*(items_tmp + 6)) * (*(m3_->items + 2)) + (*(items_tmp + 7)) * (*(m3_->items + 5)) + (*(items_tmp + 8)) * (*(m3_->items + 8));

    delete[] items_tmp;
}

void Matrix::MatrixMPoint(Point* point_){
    double x = point_->getX();
    double y = point_->getY();
    double z = point_->getZ();
    point_->setX(*(items + 0) * x + *(items + 1) * y + *(items + 2) * z);
    point_->setY(*(items + 3) * x + *(items + 4) * y + *(items + 5) * z);
    point_->setZ(*(items + 6) * x + *(items + 7) * y + *(items + 8) * z);
}
