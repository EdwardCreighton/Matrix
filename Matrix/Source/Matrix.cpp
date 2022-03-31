#include "../Headers/Matrix.h"

int Matrix::error = 0;

/*unsigned int Matrix::GetArrayIndex(unsigned int lineIndex, unsigned int columnIndex) const
{
    lineIndex = ClampValue(lineIndex, 0, lines - 1);
    columnIndex = ClampValue(columnIndex, 0, columns - 1);
    return lineIndex * columns + columnIndex;
}*/

Matrix::Matrix()
{
    lines = 0;
    columns = 0;
    linLength = 0;
    pMatrix = nullptr;
}

Matrix::Matrix(unsigned int lines, unsigned int columns)
{
    linLength = columns * lines;

    pMatrix = new double[linLength];

    if (pMatrix == nullptr)
    {
        error = -1;
        this->lines = 0;
        this->columns = 0;
        linLength = 0;

        return;
    }

    this->lines = lines;
    this->columns = columns;

    InitZeros();
}

Matrix::Matrix(const Matrix &matrixOrig)
{
    if (matrixOrig.linLength == 0)
    {
        lines = 0;
        columns = 0;
        linLength = 0;
        pMatrix = nullptr;

        return;
    }

    if (pMatrix != nullptr)
    {
        delete[] pMatrix;
        lines = 0;
        columns = 0;
        linLength = 0;
    }

    linLength = matrixOrig.lines * matrixOrig.columns;
    this->pMatrix = new double[linLength];

    if (pMatrix == nullptr)
    {
        error = -1;
        lines = 0;
        columns = 0;
        linLength = 0;

        return;
    }

    this->lines = matrixOrig.lines;
    this->columns = matrixOrig.columns;

    for (int i = 0; i < linLength; ++i)
    {
        pMatrix[i] = matrixOrig.pMatrix[i];
    }
}

Matrix::~Matrix()
{
    if (pMatrix != nullptr)
    {
        delete[] pMatrix;
        columns = 0;
        lines = 0;
        linLength = 0;
    }
}

void Matrix::InitZeros()
{
    for (int linIndex = 0; linIndex < linLength; ++linIndex)
    {
        pMatrix[linIndex] = 0;
    }
}

void Matrix::ResizeMatrix(int newLines, int newColumns)
{
    if (lines == newLines && columns == newColumns) return;

    if (newLines == 0 || newColumns == 0)
    {
        delete[] pMatrix;
        lines = 0;
        columns = 0;
        linLength = 0;

        return;
    }

    if (linLength == newLines * newColumns)
    {
        lines = newLines;
        columns = newColumns;

        return;
    }

    if (pMatrix != nullptr)
    {
        delete[] pMatrix;
    }

    linLength = newLines * newColumns;
    pMatrix = new double[linLength];

    if (pMatrix == nullptr)
    {
        error = -1;
        lines = 0;
        columns = 0;
        linLength = 0;

        return;
    }

    lines = newLines;
    columns = newColumns;

    InitZeros();
}

Matrix &Matrix::operator=(const Matrix &rightMatrix)
{
    if (pMatrix != nullptr)
    {
        delete[] pMatrix;
        lines = 0;
        columns = 0;
    }

    linLength = rightMatrix.lines * rightMatrix.columns;
    pMatrix = new double[linLength];

    if (pMatrix == nullptr)
    {
        error = -1;
        linLength = 0;

        return *this;
    }

    this->lines = rightMatrix.lines;
    this->columns = rightMatrix.columns;

    for (int i = 0; i < linLength; ++i)
    {
        this->pMatrix[i] = rightMatrix.pMatrix[i];
    }

    return *this;
}

Matrix Matrix::operator-() const
{
    Matrix newMatrix(*this);

    for (int linIndex = 0; linIndex < newMatrix.linLength; ++linIndex)
    {
        newMatrix.pMatrix[linIndex] = -newMatrix.pMatrix[linIndex];
    }

    return newMatrix;
}

Matrix &Matrix::operator+=(const Matrix &otherMatrix)
{
    if (this->lines != otherMatrix.lines || this->columns != otherMatrix.columns)
    {
        error = -3;
        return *this;
    }

    for (int linIndex = 0; linIndex < linLength; ++linIndex)
    {
        this->pMatrix[linIndex] += otherMatrix.pMatrix[linIndex];
    }

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &otherMatrix)
{
    if (this->lines != otherMatrix.lines || this->columns != otherMatrix.columns)
    {
        error = -3;
        return *this;
    }

    for (int linIndex = 0; linIndex < linLength; ++linIndex)
    {
        this->pMatrix[linIndex] -= otherMatrix.pMatrix[linIndex];
    }

    return *this;
}

Matrix &Matrix::operator*=(double value)
{
    for (int i = 0; i < GetLinLength(); ++i)
    {
        pMatrix[i] = pMatrix[i] * value;
    }

    return *this;
}

Matrix &Matrix::operator/=(double value)
{
    for (int i = 0; i < GetLinLength(); ++i)
    {
        pMatrix[i] = pMatrix[i] / value;
    }

    return *this;
}

ostream &operator<<(ostream& os, const Matrix &matrix)
{
    for (int lineIndex = 0; lineIndex < matrix.lines; ++lineIndex)
    {
        for (int columnIndex = 0; columnIndex < matrix.columns; ++columnIndex)
        {
            os << matrix.pMatrix[matrix.GetArrayIndex(lineIndex, columnIndex)] << "\t";
        }

        os << endl;
    }

    return os;
}

Matrix operator+(const Matrix &leftMatrix, const Matrix &rightMatrix)
{
    if (leftMatrix.lines != rightMatrix.lines || leftMatrix.columns != rightMatrix.columns)
    {
        Matrix::error = -3;
        return Matrix();
    }

    Matrix newMatrix(leftMatrix.lines, leftMatrix.columns);

    for (int i = 0; i < newMatrix.lines * newMatrix.columns; ++i)
    {
        newMatrix.pMatrix[i] = leftMatrix.pMatrix[i] + rightMatrix.pMatrix[i];
    }

    return newMatrix;
}

Matrix operator-(const Matrix &leftMatrix, const Matrix &rightMatrix)
{
    if (leftMatrix.lines != rightMatrix.lines || leftMatrix.columns != rightMatrix.columns)
    {
        Matrix::error = -3;
        return Matrix();
    }

    Matrix newRightMatrix = rightMatrix;
    newRightMatrix = newRightMatrix * -1;

    return leftMatrix + newRightMatrix;
}

Matrix operator*(const Matrix &matrix, double scalarValue)
{
    Matrix newMatrix(matrix.lines, matrix.columns);

    for (int i = 0; i < newMatrix.GetLinLength(); ++i)
    {
        newMatrix.pMatrix[i] = matrix.pMatrix[i] * scalarValue;
    }

    return newMatrix;
}

Matrix operator*(double scalarValue, const Matrix &matrix)
{
    return matrix * scalarValue;
}

Matrix operator/(const Matrix &matrix, double scalarValue)
{
    Matrix newMatrix(matrix.columns, matrix.lines);

    for (unsigned int i = 0; i < newMatrix.GetLinLength(); ++i)
    {
        newMatrix.pMatrix[i] /= scalarValue;
    }

    return newMatrix;
}
