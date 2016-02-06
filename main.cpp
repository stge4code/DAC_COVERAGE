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

double findCoverage(double lambda, int spacesize, double psi, double resolution, double unitcellparameter, double precise, double anglestep, double detecterdistance)
{
    Space* space = new Space(spacesize, unitcellparameter, Rotation(0, 0, 0));
    DAC* dac = new DAC(psi, Point(-1.0 / lambda, 0, 0), Rotation(0, 0, 0));
    Detector* detector = new Detector(Point(detecterdistance, 0, 0));
    Sphere* sphere_ewald = new Sphere(Point(-1.0 / lambda, 0, 0), 1.0 / lambda);
    Sphere* sphere_resolution = new Sphere(Point(0, 0, 0), 1.0 / resolution);
    space->markPoints(sphere_resolution);
    double SV = space->calcChecked();
    space->refreshCheckedPoints();
    cout << "\r" << "Resolution: " << std::setprecision(3) << std::fixed << resolution << ", "
                << "Psi: " << std::setprecision(3) << std::fixed << psi * 180 / M_PI  << "\n";
    for(double aZ = -M_PI; aZ <= M_PI; aZ += anglestep)
    //double aZ = M_PI;
    {
        //double aY = -M_PI;
        for(double aY = -M_PI; aY <= M_PI; aY += anglestep)
        {
            for(double aX = -M_PI; aX <= M_PI; aX += anglestep)
            //double aX = 0.0;
            {
                dac->setRotation(Rotation(aX, aY, aZ));
                space->setRotation(Rotation(aX, aY, aZ));
                space->rotateSpace();
                space->markPoints(dac, detector, sphere_resolution, sphere_ewald, precise);
                cout << "\r   Coverage: " << std::setprecision(2) << std::fixed << 100 * space->calcChecked() / SV << "\%" << " ("
                    << "X: " << std::setprecision(2) << std::setw(5) << aX << ",Y: "
                    << std::setprecision(2) << std::setw(5) << aY << ",Z: "
                    << std::setprecision(2) << std::setw(5) << aZ << ")";
            }
        }

    }
    double SC = space->calcChecked();
    cout << "\r                                                      \r";
    cout << "\r   Coverage: " << std::setprecision(2) << std::fixed << 100 * SC / SV << "\%\n";
    delete space;
    delete dac;
    delete detector;
    delete sphere_ewald;
    delete sphere_resolution;
    return SC / SV;
}

int main()
{

    double lambda = 0.71;
    double psi = M_PI / 4.0;
    double resolution = 0.8;
    double unitcellparameter = 3.0;
    double precise = 1E-4;
    double anglestep = 0.05;
    double detecterdistance = 5.0;
    int spacesize = 10;
    ofstream fout;
    fout.open("output.txt");
    fout << std::setw(20) << "resolution" << " " << std::setw(20) <<  "\%" << "\n";
    fout.close();
    for(double r = 1.0; r > 0; r -= 0.05)
    {
        fout.open("output.txt", ios::app);
        fout << std::setprecision(3) << std::fixed << std::setw(20) << r << " " << std::setw(20) << findCoverage(lambda, spacesize, psi, r, unitcellparameter, precise, anglestep, detecterdistance) << "\n";
        fout.close();
    }
    fout.open("output.txt", ios::app);
    fout << "\n";
    fout << std::setw(20) << "psi" << " " << std::setw(20) <<  "\%(resolution = 0.8)" << "\n";
    fout.close();
    for(double p = M_PI / 2.0; p  >= 0; p  -= 0.05)
    {
        fout.open("output.txt", ios::app);
        fout << std::setprecision(3) << std::fixed << std::setw(20) << p * 180 / M_PI << " " << std::setw(20) << findCoverage(lambda, p, spacesize, resolution, unitcellparameter, precise, anglestep, detecterdistance) << "\n";
        fout.close();
    }
    return 0;
}
