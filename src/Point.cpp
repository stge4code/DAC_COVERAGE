#include "Point.h"

Point::Point()
{
}

Point::Point(double x_, double y_, double z_): x(x_), y(y_), z(z_)
{
    check = false;
}
Point::~Point()
{
}
double Point::getX() const
{
    return x;
};
double Point::getY() const
{
    return y;
};
double Point::getZ() const
{
    return z;
};

void Point::setX(double x_)
{
    x = x_;
};
void Point::setY(double y_)
{
    y = y_;
};
void Point::setZ(double z_)
{
    z = z_;
};
void Point::setCheck(bool check_)
{
    check = check_;
};

bool Point::getCheck()
{
    return check;
}

