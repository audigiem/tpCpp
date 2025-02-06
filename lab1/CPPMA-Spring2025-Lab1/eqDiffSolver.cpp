//
// Created by audigiem on 06/02/25.
//

#include <cstdlib>
#include <iostream>
#include <cmath>

double getNthNode(double xInitial, double step, int n) {
    return xInitial + n * step;
}

double *phi(double x, double *y) {
    double *result = static_cast<double *>(malloc(sizeof(double)));
    result[0] = 50*cos(x)*y[0];
    return result;
}


double *eulerExplicit(double xInitial, double yInitial, double step, int nbIter) {
    double *y = static_cast<double *>(malloc(nbIter * sizeof (double)));
    y[0] = yInitial;
    for (int i = 1; i < nbIter; i++) {
        y[i] = step * (phi(getNthNode(xInitial, step, i), y)[0]) + y[i-1];
    }
    return y;
}


int main() {
    double xInitial = 0;
    double yInitial = 2;
    double step = 0.001;
    int nbIter = 2000;
    double *y = eulerExplicit(xInitial, yInitial, step, nbIter);
    for (int i = 0; i < nbIter; i++) {
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }
    return 0;
}