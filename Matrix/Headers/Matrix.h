#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream> // for "cout" and "string"
#include <sstream> // for "basic_istringstream"
#include <cmath> // abs, sqrt

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
                if (matrix(lineIndex, columnIndex) - matrix(columnIndex, lineIndex) > FloatEps)
                {
                    return false;
                }
            }
        }

        return true;
    }

    // Matrix interface
    void ResizeMatrix(unsigned int newLines = 0, unsigned int newColumns = 0);

    void SetValue(unsigned int lineIndex = 0, unsigned int columnIndex = 0, double value = 0.0);
    void SetValues(const string& values);
    double GetValue(unsigned int lineIndex = 0, unsigned int columnIndex = 0) const;

    // Matrix computations
    Matrix Transpose() const;

    void LU(Matrix &matrixL, Matrix &matrixU) const;
    double DetLU() const;
    static double DetLU(const Matrix &upTriMatrix);
    /// \Form A*X=F
    Matrix SolveLU(const Matrix &matrixF, double *pDet = nullptr) const;
    Matrix InvLU(double *pDet = nullptr) const;

    void QR_Givens(Matrix &matrixQ, Matrix &matrixR) const;
    double DetQR() const;
    static double DetQR(const Matrix &rightTriMatrix);
    Matrix SolveQR(const Matrix &matrixF, double *pDet = nullptr) const;
    Matrix InvQR(double *pDet = nullptr) const;

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

    inline double& operator()(unsigned int line, unsigned int column) const
    {
        return this->pMatrix[line * columns + column];
    }

    inline void operator()(unsigned int line, unsigned int column, double value) const
    {
        this->pMatrix[line * columns + column] = value;
    }
};

#endif //MATRIX_MATRIX_H
