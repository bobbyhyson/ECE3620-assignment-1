//
// Created by Bobby Thompson on 10/3/25.
//

#ifndef ECE3620_ASSIGNMENT_1_EQUATIONS_H
#define ECE3620_ASSIGNMENT_1_EQUATIONS_H

 void ode_solve(const double a, double deltat, double y0, int N) {
    int i;
     double t = 0.0;
     double  y = y0;

     std::cout << "First ODE solved: "<< std::endl;
    for (i = 0; i < N; i++) {
        y = (1-a*deltat)*y;
        double t =(i + 1)*deltat;
        std::cout << t << " " << y << std::endl;
    }
     std::cout << "\n" << std::endl;
}
void mattimes(double deltat2, double a2[][3], double m2[][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            m2[i][j] = deltat2*a2[i][j];
            std::cout << m2[i][j] << std::endl;
        }
    }
     std::cout << "\nmattimes output ^^^^^^" << std::endl;
}

void matsub(double a2[][3], double b[][3], double c[][3]) {
     int i, j;
     for (i = 0; i < 3; i++){
         for (j = 0; j < 3; j++) {
             c[i][j] = a2[i][j]-b[i][j];
             std::cout << c[i][j] << std::endl;
         }
     }
     std::cout << "\nmatsub output ^^^^^^" << std::endl;
 }
void matvecmult(double m2[][3],const double *v, double *prod) {
    double sum;
    int i, j;
    for (i = 0; i < 3; i++){
        sum = 0;
        for (j = 0; j < 3; j++) {
            sum += m2[i][j] * v[j];
            prod[i] = sum;
            std::cout << prod[i] << std::endl;
        }
    }
     std::cout << "\nmatvecmult output ^^^^^^" << std::endl;
}

#endif //ECE3620_ASSIGNMENT_1_EQUATIONS_H