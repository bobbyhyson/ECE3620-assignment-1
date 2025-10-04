#include <iostream>
#include <fstream>
#include "equations.h"

void mattimes(double deltat2, double a2[][3], double m2[][3]);
void matsub(double a2[][3], double b[][3], double c[][3]);
void matvecmult(double m2[][3],const double *v, double *prod);

int main() {
    //first order eq
    double a = 2.5;
    double y0 = 3;
    double T = .8;
    double deltat = 10;
    double deltat2 = 2;
    int N = (int)(T/deltat);

    ode_solve(a, deltat, y0, N);

    //third order eq
    double a2[3][3] = {{0, 1, 0},{0,0,1},{2.5063,25.1125,0.6}};
    double m2[3][3];
    double v[3] = {1.5, 2, -1};
    double prod[3];
    double I2[3][3] = {{1,0,0,},{0,1,0},{0,0,1}};


    mattimes(deltat2, a2, m2);
    //std::cout <<"\n" << m2[3][3] << " first m2 mainfile" << std::endl;
    matsub(I2, a2, m2);
    //std::cout << m2[3] << " mainfile" << std::endl;
    matvecmult(I2, v, prod);
    //std::cout << prod[3] << " mainfile" << std::endl;

    return 0;









}