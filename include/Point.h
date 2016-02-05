#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point();
    Point(double, double, double);
    virtual ~Point();
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double);
    void setY(double);
    void setZ(double);
    void setCheck(bool);
    bool getCheck();
protected:
private:
    double x;
    double y;
    double z;
    bool check = false;
};

#endif // POINT_H
