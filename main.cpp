#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>
#include "Point.h"
#include "Matrix.h"
#include "Rotation.h"
#include "Sphere.h"
#include "Space.h"
#include "DAC.h"
#include "Detector.h"
#include <thread>
#include <string>


# define M_PI           3.14159265358979323846  /* pi */
using namespace std;

void findCoverage(double lambda, int spacesize, double psi, double resolution, double unitcellparameter, double precise, double anglestep, double detecterdistance, std::ostringstream& resultbuffer)
{
    DAC* dac = new DAC(psi, Point(-1.0 / lambda, 0, 0), Rotation(0, 0, 0));
    Detector* detector = new Detector(Point(detecterdistance, 0, 0));
    Sphere* sphere_ewald = new Sphere(Point(-1.0 / lambda, 0, 0), 1.0 / lambda);
    Sphere* sphere_resolution = new Sphere(Point(0, 0, 0), 1.0 / (2.0 * resolution));
    Space* space = new Space(spacesize, unitcellparameter, Rotation(0, 0, 0), sphere_resolution);
    double SV = space->getVolume();
    for(double aZ = -M_PI; aZ <= M_PI; aZ += anglestep)
    {
        for(double aY = -M_PI; aY <= M_PI; aY += anglestep)
        {
            for(double aX = -M_PI; aX <= M_PI; aX += anglestep)
            {
                dac->setRotation(Rotation(aX, aY, aZ));
                space->setRotation(Rotation(aX, aY, aZ));
                space->markPoints(dac, detector, sphere_ewald, precise);
            }
        }

    }
    double SC = space->calcChecked();
    cout << "Res: " << std::setprecision(3) << std::fixed << resolution << ", "
         << "Psi: " << std::setprecision(3) << std::fixed << psi * 180 / M_PI  << " Cov: " << std::setprecision(2) << std::fixed << 100 * SC / SV << "\%"
         << " Vol: " << (long) SC << " VolTotal: " << (long) SV << "  " << "\n";
    delete space;
    delete dac;
    delete detector;
    delete sphere_ewald;
    delete sphere_resolution;
    double result = SC / SV;
    resultbuffer << std::setprecision(3) << std::fixed << std::setw(20) << psi * 180 / M_PI << " " << std::setprecision(3) << std::fixed << std::setw(20) << resolution << " " << std::setw(20) <<  result << "\n";
}

void readParameters(std::ifstream &fin,  double& lambda,
                    double& psi, double& psi_l, double& psi_r, double& psi_step,
                    double& resolution, double& resolution_l, double& resolution_r, double& resolution_step,
                    double& unitcellparameter, double& precise, double& anglestep, double& detecterdistance, int& spacesize, int& threads)
{
    string name;
    double value;
    if( !fin )
        cerr << "Cant open " << endl;
    while(fin >> name >> value)
    {
        if(name.compare("lambda") == 0)
        {
            lambda = value;
            cout << std::setw(20) << "lambda " << lambda << "\n";
            continue;
        }
        if(name.compare("psi") == 0)
        {
            psi = value * M_PI / 180.0;
            cout << std::setw(20) << "psi " <<  value << "\n";
            continue;
        }
        if(name.compare("psi_r") == 0)
        {
            psi_r = value * M_PI / 180.0;
            cout << std::setw(20) << "psi_r " <<  value << "\n";
            continue;
        }
        if(name.compare("psi_l") == 0)
        {
            psi_l = value * M_PI / 180.0;
            cout << std::setw(20) << "psi_l " <<  value << "\n";
            continue;
        }

        if(name.compare("psi_step") == 0)
        {
            psi_step = value * M_PI / 180.0;
            cout << std::setw(20) << "psi_step " <<  value << "\n";
            continue;
        }

        if(name.compare("resolution") == 0)
        {
            resolution = value;
            cout << std::setw(20) << "resolution " << resolution << "\n";
            continue;
        }
        if(name.compare("resolution_l") == 0)
        {
            resolution_l = value;
            cout << std::setw(20) << "resolution_l " << resolution_l << "\n";
            continue;
        }

        if(name.compare("resolution_r") == 0)
        {
            resolution_r = value;
            cout << std::setw(20) << "resolution_r " << resolution_r << "\n";
            continue;
        }

        if(name.compare("resolution_step") == 0)
        {
            resolution_step = value;
            cout << std::setw(20) << "resolution_step " << resolution_step << "\n";
            continue;
        }

        if(name.compare("unitcellparameter") == 0)
        {
            unitcellparameter = value;
            cout << std::setw(20) << "unitcellparameter " << unitcellparameter << "\n";
            continue;
        }
        if(name.compare("precise") == 0)
        {
            precise = value;
            cout << std::setw(20) << "precise " << precise << "\n";
            continue;
        }
        if(name.compare("anglestep") == 0)
        {
            anglestep = value * M_PI / 180.0;
            cout << std::setw(20) << "anglestep " << value << "\n";
            continue;
        }
        if(name.compare("detecterdistance") == 0)
        {
            detecterdistance = value;
            cout << std::setw(20) << "detecterdistance " << detecterdistance << "\n";
            continue;
        }

        if(name.compare("spacesize") == 0)
        {
            spacesize = (int) value;
            cout << std::setw(20) << "spacesize " << spacesize << "\n";
            continue;
        }

        if(name.compare("threads") == 0)
        {
            threads = (int) value;
            cout << std::setw(20) << "threads " << threads << "\n";
        }
    }
}

int main(int argc, char* argv[])
{



    double lambda = 0.71;
    double psi = M_PI / 4.0;
    double psi_l = M_PI / 30.0;
    double psi_r = M_PI / 2.0;
    double psi_step = M_PI / 30.0;
    double resolution = 0.8;
    double resolution_l = 0.7;
    double resolution_r = 1.0;
    double resolution_step = 1.0;
    double unitcellparameter = 3.0;
    double precise = 1E-3;
    double anglestep = M_PI / 80.0;
    double detecterdistance = 5.0;
    int spacesize = 10;
    int threads = 7;


    if (argc > 1)
    {
        cout << "Input file: " << argv[1] << endl;
    }
    else
    {
        cout << "No file name entered. Exiting...";
        return -1;
    }
    ifstream fin(argv[1]);
    readParameters(fin, lambda, psi, psi_l, psi_r, psi_step, resolution, resolution_l, resolution_r, resolution_step, unitcellparameter, precise, anglestep, detecterdistance, spacesize, threads);
    fin.close();

    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);

    std::thread THREADS[threads];
    ofstream fout;
    fout.open("output.txt");
    fout << std::setprecision(3) << std::setw(20) << "psi" << " " << std::setw(20) << "resolution" << " " << std::setw(20) <<  "\%" << "\n";
    for(double r = resolution_r; r >= resolution_l; r -= threads * resolution_step)
    {
        std::ostringstream resultbuffer;
        for(int i = 0; i < threads; i++)
        {
            if(r - i * resolution_step >= resolution_l) THREADS[i] = std::thread(findCoverage, lambda, spacesize, psi, r - i * resolution_step, unitcellparameter, precise, anglestep, detecterdistance, std::ref(resultbuffer));
        }
        for(int i = 0; i < threads; i++)
        {
            if(r - i * resolution_step >= resolution_l) THREADS[i].join();
        }
        fout << resultbuffer.str();
    }
    fout << "\n";
    for(double p = psi_r; p  >= psi_l; p  -= threads * psi_step)
    {
        std::ostringstream resultbuffer;
        for(int i = 0; i < threads; i++)
        {
            if(p - i * psi_step >= psi_l) THREADS[i] = std::thread(findCoverage, lambda, spacesize, p - i * psi_step, resolution, unitcellparameter, precise, anglestep, detecterdistance, std::ref(resultbuffer));
        }
        for(int i = 0; i < threads; i++)
        {
            if(p - i * psi_step >= psi_l) THREADS[i].join();
        }
        fout << resultbuffer.str();
    }
    fout.close();
    return 0;
}
