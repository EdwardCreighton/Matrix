#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
private:
    int columns;
    int lines;
    double *matrix;

public:
    Matrix(int columns, int lines);

    void InitMatrix();
    void PrintMatrix();

    ~Matrix();
};


#endif //MATRIX_MATRIX_H
