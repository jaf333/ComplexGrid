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

// array Initialization 

ComplexArray* createComplexArray(const int* shape, int ndim) {
    if (ndim <= 0) {
        fprintf(stderr, "Cannot initialize Array of dimensions %d", ndim);
        exit(1);
    }

    ComplexArray* arr = (ComplexArray*)malloc(sizeof(ComplexArray));
    _checkNull(arr);

    arr->ndim = ndim;
    arr->shape = (int*)malloc(arr->ndim * sizeof(int));
    arr->strides = (int*)malloc(arr->ndim * sizeof(int));
    arr->backstrides = (int*)malloc(arr->ndim * sizeof(int));

    _checkNull(arr->shape);
    _checkNull(arr->strides);
    _checkNull(arr->backstrides);

    arr->itemsize = sizeof(Complex);
    arr->totalsize = 1;

    for (int i = 0; i < arr->ndim; i++) {
        arr->shape[i] = shape[i];
        arr->totalsize *= shape[i];
    }

    arr->data = (Complex*)malloc(arr->totalsize * arr->itemsize);
    _checkNull(arr->data);

    // Calculate strides and backstrides
    arr->strides[arr->ndim - 1] = arr->itemsize;
    for (int i = arr->ndim - 2; i >= 0; i--) {
        arr->strides[i] = arr->strides[i + 1] * arr->shape[i + 1];
    }
    for (int i = arr->ndim - 1; i >= 0; i--) {
        arr->backstrides[i] = -1 * arr->strides[i] * (arr->shape[i] - 1);
    }
    arr->C_ORDER = (arr->strides[arr->ndim - 1] == arr->itemsize);
    arr->F_ORDER = (arr->strides[0] == arr->itemsize);

    return arr;
}

void freeComplexArray(ComplexArray* arr) {
    free(arr->data);
    free(arr->shape);
    free(arr->strides);
    free(arr->backstrides);
    free(arr);
}

// Array operations 

void fillRandomComplex(ComplexArray* arr) {
    srand(time(NULL));
    for (int i = 0; i < arr->totalsize; i++) {
        arr->data[i] = _getRandomComplex();
    }
}

ComplexArray* addComplexArrays(ComplexArray* a, ComplexArray* b) {
    if (a->totalsize != b->totalsize) {
        fprintf(stderr, "Array sizes do not match for addition.\n");
        exit(1);
    }

    ComplexArray* result = createComplexArray(a->shape, a->ndim);

    #pragma omp parallel for
    for (int i = 0; i < a->totalsize; i++) {
        result->data[i] = a->data[i] + b->data[i];
    }

    return result;
}


// traverse and display 

void printComplexArray(ComplexArray* arr) {
    for (int i = 0; i < arr->totalsize; i++) {
        printf("(%.2f, %.2f) ", creal(arr->data[i]), cimag(arr->data[i]));
        if ((i + 1) % arr->shape[arr->ndim - 1] == 0) {
            printf("\n");
        }
    }
}

