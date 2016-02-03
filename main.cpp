#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <fstream>
#include "Point.h"
#include "Sphere.h"
#include "Space.h"
# define M_PI           3.14159265358979323846  /* pi */
using namespace std;


double findCoverage(double angle, double resolution, double accuracy, Space* space){
    space->refreshCheckedPoints();
    Sphere* sphere_resolution = new Sphere(Point(0.0, 0.0, 0.0), resolution);
    Sphere* sphere_ewald = new Sphere(Point(0.5 * sin(angle), 0.0, -0.5 * cos(angle)), 0.5);
    for(double phi = 0; phi < 2 * M_PI; phi += accuracy)
    {
        sphere_ewald->moveCenter(phi);
        space->markPoints(sphere_ewald, sphere_resolution);
    }
    double in_ewald = space->calcChecked();
    space->refreshCheckedPoints();
    space->markPoints(sphere_resolution);
    double in_resolution = space->calcChecked();
    space->refreshCheckedPoints();
    delete sphere_resolution;
    delete sphere_ewald;
    return in_ewald / in_resolution;
}

int main()
{
    ofstream fout;
    Space* space = new Space(100);
    fout.open("output.txt");
    fout << std::setw(20) << "theta" << " " << std::setw(20) <<  "\%" << "\n";
    for(double r = 1.0; r >= 0; r -= 0.05) {
            fout << std::setprecision(3) << std::fixed << std::setw(20) << asin(r) * 180 / M_PI << " " << std::setw(20) << findCoverage(M_PI / 4.0, r, 0.05, space) << "\n";
    }
    fout << "\n";
    fout << std::setw(20) << "alpha" << " " << std::setw(20) <<  "\%(theta = 45)" << "\n";
    for(double alpha = M_PI / 2.0; alpha >= 0; alpha -= 0.1) {
            fout << std::setprecision(3) << std::fixed << std::setw(20) << alpha * 180 / M_PI << " " << std::setw(20) << findCoverage(alpha, .5, 0.05, space) << "\n";
    }
    fout.close();
    return 0;
}
