#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <fstream>
#include "Point.h"
#include "Matrix.h"
#include "Rotation.h"
#include "Sphere.h"
#include "Space.h"
#include "DAC.h"
#include "Detector.h"


# define M_PI           3.14159265358979323846  /* pi */
using namespace std;

int main()
{
    /*ofstream fout;
    Space* space = new Space(100);
    fout.open("output.txt");
    fout << std::setw(20) << "theta" << " " << std::setw(20) <<  "\%" << "\n";
    for(double r = 1.0; r >= 0; r -= 0.05) {
            fout << std::setprecision(3) << std::fixed << std::setw(20) << asin(r) * 180 / M_PI << " " << std::setw(20) << findCoverage(M_PI / 4.0, r, 0.05, space) << "\n";
    }
    fout << "\n";
    fout << std::setw(20) << "alpha" << " " << std::setw(20) <<  "\%(theta = 45)" << "\n";
    for(double alpha = M_PI / 2.0; alpha >= 0; alpha -= 0.05) {
            fout << std::setprecision(3) << std::fixed << std::setw(20) << alpha * 180 / M_PI << " " << std::setw(20) << findCoverage(alpha, .5, 0.05, space) << "\n";
    }
    fout.close();
    return 0;*/
    double lambda = 0.71;
    double psi = M_PI / 4.0;
    double resolution = 1.0;
    double unitcellparameter = 7.0;
    double precise = 1E-2;
    double anglestep = 5E-1;
    double detecterdistance = 10.0;

    int spacesize = unitcellparameter / resolution / sqrt(3.0);
    Space* space = new Space(spacesize, unitcellparameter, Rotation(0, 0, 0));
    DAC* dac = new DAC(psi, Point(-1.0 / lambda, 0, 0), Rotation(0, 0, 0));
    Detector* detector = new Detector(Point(detecterdistance, 0, 0));
    Sphere* sphere_ewald = new Sphere(Point(-1.0 / lambda, 0, 0), 1.0 / lambda);
    for(double aZ = -M_PI; aZ <= M_PI; aZ += anglestep)
    {
        for(double aY = -M_PI; aY <= M_PI; aY += anglestep)
        {
            for(double aX = -M_PI; aX <= M_PI; aX += anglestep)
            {
                dac->setRotation(Rotation(aX, aY, aZ));
                space->setRotation(Rotation(aX, aY, aZ));
                space->rotateSpace();
                space->markPoints(dac, sphere_ewald, detector, precise);
            }
        }
    }
    cout << (double) space->calcChecked() / space->getVolume();
    return 0;
}
