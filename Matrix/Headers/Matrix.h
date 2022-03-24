#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
private:
    unsigned int columns;
    unsigned int lines;
    unsigned int linLength;

    double* pMatrix;

    /// \values
    /// -3: unequal matrices
    /// -2: resize failed;
    /// -1: memory allocation failed;
    /// 0: no errors;
    static int error;

    static unsigned int ClampValue(unsigned int value, unsigned int minValue, unsigned int maxValue)
    {
        if (value > maxValue) return maxValue;
        if (value < minValue) return minValue;
        return value;
    }
    unsigned int GetArrayIndex(unsigned int lineIndex, unsigned int columnIndex) const;
    unsigned int GetLinLength()
    {
        return linLength;
    }
    void InitZeros();

public:
    Matrix();
    Matrix(unsigned int lines, unsigned int columns);
    Matrix(const Matrix& matrixOrig);
    ~Matrix();

    static int GetErrorCode()
    {
        return error;
    }
    static void ResetErrorCode(int newErrorCode = 0)
    {
        error = newErrorCode;
    }

    void ResizeMatrix(int newLines, int newColumns);

    void SetValue(int lineIndex, int columnIndex, double& value)
    {
        pMatrix[GetArrayIndex(lineIndex, columnIndex)] = value;
    }
    double GetValue(int lineIndex, int columnIndex)
    {
        return pMatrix[GetArrayIndex(lineIndex, columnIndex)];
    }

    Matrix& operator=(const Matrix& rightMatrix);
    Matrix operator-() const;

    Matrix& operator+=(const Matrix &otherMatrix);

    friend ostream& operator<<(ostream& os, const Matrix& matrix);

    friend Matrix operator+(const Matrix& leftMatrix, const Matrix& rightMatrix);
    friend Matrix operator-(const Matrix& leftMatrix, const Matrix& rightMatrix);

    friend Matrix operator*(const Matrix &matrix, double scalarValue);
    friend Matrix operator*(double scalarValue, const Matrix &matrix);
    friend Matrix operator/(const Matrix &matrix, double scalarValue);
};

#endif //MATRIX_MATRIX_H
