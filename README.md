# ComplexGrid
A lightweight C library for handling complex numbers in multidimensional arrays, inspired by numpy but simplified for educational purposes

## Features
- Define array structure for complex numbers.
- Create and initialize arrays with complex numbers.
- Support for basic arithmetic (addition).
- Traverse and display the array.

## Installation
To compile and run this library, you need a C compiler (e.g., gcc).

```sh
gcc complex_grid.c -o complex_grid -lm -fopenmp
./complex_grid
```

## Usage
The library allows you to create, initialize, and perform operations on multidimensional arrays of complex numbers.

## Example

```
const int shape[] = {3, 3};
ComplexArray* array1 = createComplexArray(shape, 2);
ComplexArray* array2 = createComplexArray(shape, 2);

fillRandomComplex(array1);
fillRandomComplex(array2);

ComplexArray* sumArray = addComplexArrays(array1, array2);

printComplexArray(sumArray);

freeComplexArray(array1);
freeComplexArray(array2);
freeComplexArray(sumArray);
```
