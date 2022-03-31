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
    /// -4: index out of range;
    /// -3: unequal matrices;
    /// -2: resize failed;
    /// -1: memory allocation failed;
    /// 0: no errors;
    static int error;

    inline unsigned int ClampValue(unsigned int value, unsigned int maxValue)
    {
        if (value > maxValue) return maxValue;
        return value;
    }
    inline unsigned int GetArrayIndex(unsigned int lineIndex, unsigned int columnIndex) const
    {
        return lineIndex * columns + columnIndex;
    }
    inline unsigned int GetLinLength() const
    {
        return linLength;
    }
    void InitZeros();

public:
    //Matrix();
    Matrix(unsigned int lines = 0, unsigned int columns = 0);
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

    void ResizeMatrix(int newLines = 0, int newColumns = 0);

    void SetValue(int lineIndex = 0, int columnIndex = 0, double value = 0.0)
    {
        if (linLength == 0)
        {
            error = -4;
            return;
        }

        pMatrix[GetArrayIndex(ClampValue(lineIndex, lines - 1),
                              ClampValue(columnIndex, columns - 1))]
                              = value;
    }
    double GetValue(int lineIndex = 0, int columnIndex = 0)
    {
        if (linLength == 0)
        {
            error = -4;
            return 0.0;
        }

        return pMatrix[GetArrayIndex(ClampValue(lineIndex, lines - 1),
                                     ClampValue(columnIndex, columns - 1))];
    }

    Matrix& operator=(const Matrix& rightMatrix);
    Matrix operator-() const;

    Matrix& operator+=(const Matrix &otherMatrix);
    Matrix& operator-=(const Matrix &otherMatrix);
    Matrix& operator*=(double value);
    Matrix& operator/=(double value);

    friend ostream& operator<<(ostream& os, const Matrix& matrix);

    friend Matrix operator+(const Matrix& leftMatrix, const Matrix& rightMatrix);
    friend Matrix operator-(const Matrix& leftMatrix, const Matrix& rightMatrix);

    friend Matrix operator*(const Matrix &matrix, double scalarValue);
    friend Matrix operator*(double scalarValue, const Matrix &matrix);
    friend Matrix operator/(const Matrix &matrix, double scalarValue);
};

#endif //MATRIX_MATRIX_H
