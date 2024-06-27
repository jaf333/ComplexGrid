// complex_grid.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>
#include <math.h>
#include <time.h>
#include <omp.h>

typedef double complex Complex;

typedef struct {
    Complex* data;
    int* shape;
    int* strides;
    int* backstrides;
    int ndim;
    int itemsize;
    int totalsize;
    bool C_ORDER;
    bool F_ORDER;
} ComplexArray;

// Utility functions for ComplexGrid

void _checkNull(void* value) {
    if (value == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
}

Complex _getRandomComplex() {
    double real = (double)rand() / RAND_MAX * 2.0 - 1.0;
    double imag = (double)rand() / RAND_MAX * 2.0 - 1.0;
    return real + I * imag;
}
