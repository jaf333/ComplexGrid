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
