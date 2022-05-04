#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream> // for "cout" and "string"
#include <sstream> // for "basic_istringstream"
#include <cmath>

using namespace std;

class Matrix
{
private:
    unsigned int columns;
    unsigned int lines;
    unsigned int linLength;

    double* pMatrix;

    /// \Computations
    /// -11: not corresponding matrices;
    /// -10: non-square matrix;
    /// \Regular
    /// -4: index out of range;
    /// -3: unequal matrices;
    /// -2: resize failed;
    /// -1: memory allocation failed;
    /// 0: no errors;
    static int error;

    static const double FloatEps;

    inline static unsigned int ClampValue(unsigned int value, unsigned int maxValue)
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

    // Internal computations
    static void LUD(const Matrix& matrixA, Matrix& matrixL, Matrix& matrixU);
    static void ChD(const Matrix& matrixA, Matrix& matrixL, Matrix& matrixU);

    static void GivensRotation(double a, double b, double &c, double &s);

    void InitZeros();

public:
    Matrix();
    Matrix(unsigned int lines, unsigned int columns = 0);
    Matrix(const Matrix& matrixOrig);
    ~Matrix();

    // Static functions
    inline static int GetErrorCode()
    {
        return error;
    }
    inline static void ResetErrorCode(int newErrorCode = 0)
    {
        error = newErrorCode;
    }

    inline static bool MatricesEqual(const Matrix &matrixA, const Matrix &matrixB)
    {
        return matrixA.lines == matrixB.lines && matrixA.columns == matrixB.columns;
    }
    inline static bool CheckSymmetric(const Matrix& matrix)
    {
        if (matrix.lines != matrix.columns) return false;

        for (int lineIndex = 0; lineIndex < matrix.lines; ++lineIndex)
        {
            for (int columnIndex = 0; columnIndex < matrix.columns; ++columnIndex)
            {
                if (matrix.GetValue(lineIndex, columnIndex) - matrix.GetValue(columnIndex, lineIndex) > FloatEps)
                {
                    return false;
                }
            }
        }

        return true;
    }

    // Matrix interface
    void ResizeMatrix(unsigned int newLines = 0, unsigned int newColumns = 0);

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
    void SetValues(const string& values);
    double GetValue(int lineIndex = 0, int columnIndex = 0) const
    {
        if (linLength == 0)
        {
            error = -4;
            return 0.0;
        }

        return pMatrix[GetArrayIndex(ClampValue(lineIndex, lines - 1),
                                     ClampValue(columnIndex, columns - 1))];
    }

    // Matrix computations
    static void MatrixDecomposition(const Matrix &matrixA, Matrix &matrixL, Matrix &matrixU);
    void LUDecomposition(Matrix &matrixL, Matrix &matrixU) const;
    void QR_Givens(Matrix &matrixQ, Matrix &matrixR) const;
    double Det() const;
    static double Det(const Matrix &matrixU);
    /// \Form A*X=F
    Matrix SolveLU(const Matrix &matrixF, double *pDet = nullptr) const;
    Matrix InvLU(double *pDet= nullptr) const;


    // Operators' overloading
    Matrix& operator=(const Matrix& rightMatrix);
    Matrix operator-() const;

    Matrix& operator+=(const Matrix &otherMatrix);
    Matrix& operator-=(const Matrix &otherMatrix);
    Matrix& operator*=(double value);
    Matrix& operator*=(const Matrix& otherMatrix);
    Matrix& operator/=(double value);

    friend ostream& operator<<(ostream& os, const Matrix& matrix);

    friend Matrix operator+(const Matrix& leftMatrix, const Matrix& rightMatrix);
    friend Matrix operator-(const Matrix& leftMatrix, const Matrix& rightMatrix);

    friend Matrix operator*(const Matrix &matrix, double scalarValue);
    friend Matrix operator*(double scalarValue, const Matrix &matrix);
    friend Matrix operator*(const Matrix &matrixLeft, const Matrix& matrixRight);
    friend Matrix operator/(const Matrix &matrix, double scalarValue);
};

#endif //MATRIX_MATRIX_H
