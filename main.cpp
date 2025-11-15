#include <iostream>
#include <fstream>
#include "equations.h"

void mattimes(double deltat2, double a2[][3], double m2[][3]);
void matsub(double a2[][3], double b[][3], double c[][3]);
void matvecmult(double m2[][3],const double *v, double *prod);
void ode_solve(double a, double deltat, double y0, int N);
void matadd(double a2[][3], double B[][3], double C[][3]);

int main() {
    //first order eq
    double a = 2.5;
    double y0 = 3.0;
    double T = 10.0;
    double deltat = 0.25;
    int N = (int)(T/deltat);

    ode_solve(a, deltat, y0, N);

    //third order eq
    double a2[3][3] = {{0, 1, 0},{0,0,1},{-2.5063,-25.1125,-0.6}};
    double dtA[3][3];
    double phi[3][3];

    double v[3] = {1.5, 2, -1};
    double vnext[3];

    double prod[3];
    double I2[3][3] = { {1,0,0,},{0,1,0},{0,0,1}};
    double deltat2 = 0.01;
    int N2 = (int)(T/deltat2);

    mattimes(deltat2, a2, dtA);
    matadd(I2, dtA, phi);
    std::ofstream out("Third_order.txt");
    double t = 0.0;

    out << t << " " << v[0] << " " << v[1] << " " << v[2] << "\n";

    for (int k = 0; k < N2; ++k) {
        matvecmult(phi, v, vnext);
        v[0] = vnext[0];
        v[1] = vnext[1];
        v[2] = vnext[2];

        t += deltat2;
        out << t << " " << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
    out.close();

    //std::cout <<"\n" << m2[3][3] << " first m2 mainfile" << std::endl;
    matsub(I2, a2, dtA);
    //std::cout << m2[3] << " mainfile" << std::endl;
    matvecmult(I2, v, prod);
    //std::cout << prod[3] << " mainfile" << std::endl;

    return 0;









}