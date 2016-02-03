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
    double x = 0;
    double y = 0;
    double z = 0;
    bool check = false;
};

#endif // POINT_H
