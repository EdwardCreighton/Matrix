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

    int GetIndex(int columnIndex, int lineIndex);

public:
    Matrix(int columns, int lines);

    void SimpleInitMatrix();
    void PrintMatrix();

    void SetValue(int columnIndex, int lineIndex, double &value);
    double GetValue(int columnIndex, int lineIndex);



    ~Matrix();
};


#endif //MATRIX_MATRIX_H
