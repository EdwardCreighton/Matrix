#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
private:
    int columns;
    int lines;
    double* matrix;

    int GetIndex(int columnIndex, int lineIndex);
    friend bool MatricesEqual(const Matrix& matrix1, const Matrix& matrix2);

public:
    Matrix(int columns, int lines);
    Matrix(const Matrix& matrixOrig);

    void SimpleInitMatrix();
    void PrintMatrix();

    void SetValue(int columnIndex, int lineIndex, double& value);
    double GetValue(int columnIndex, int lineIndex);

    Matrix& operator=(const Matrix& rightMatrix);

    friend const Matrix operator+(const Matrix& leftMatrix, const Matrix& rightMatrix);
    friend const Matrix operator-(const Matrix& leftMatrix, const Matrix& rightMatrix);

    friend const Matrix operator*(const Matrix& matrix, double scalarValue);
    friend const Matrix operator*(double scalarValue, const Matrix& matrix);

    ~Matrix();
};


#endif //MATRIX_MATRIX_H
