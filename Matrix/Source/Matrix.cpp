#include "../Headers/Matrix.h"

Matrix::Matrix(int columns, int lines)
{
    this->lines = lines;
    this->columns = columns;

    int length = columns * lines;

    matrix = new double[length];

    SimpleInitMatrix();
}

Matrix::Matrix(const Matrix &matrixOrig)
{
    if (matrix != nullptr)
    {
        delete[] matrix;
    }

    this->matrix = new double[matrixOrig.lines * matrixOrig.columns];

    this->lines = matrixOrig.lines;
    this->columns = matrixOrig.columns;

    for (int i = 0; i < lines * columns; ++i)
    {
        matrix[i] = matrixOrig.matrix[i];
    }
}

Matrix::~Matrix()
{
    delete[] matrix;
}

void Matrix::SimpleInitMatrix()
{
    for (int i = 0; i < lines * columns; ++i)
    {
        matrix[i] = i + 1;
    }
}

void Matrix::PrintMatrix()
{
    cout << matrix << endl;

    for (int columnsCount = 0; columnsCount < lines * columns; ++columnsCount)
    {
        if (columnsCount % columns == 0)
        {
            cout << endl;
        }

        cout << matrix[columnsCount] << "\t";
    }
}

void Matrix::SetValue(int columnIndex, int lineIndex, double& value)
{
    matrix[GetIndex(columnIndex, lineIndex)] = value;
}

double Matrix::GetValue(int columnIndex, int lineIndex)
{
    return matrix[GetIndex(columnIndex, lineIndex)];
}

int Matrix::GetIndex(int columnIndex, int lineIndex)
{
    return lineIndex * columns + columnIndex;
}

bool MatricesEqual(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.lines != matrix2.lines || matrix1.columns != matrix2.columns) return false;

    return true;
}

Matrix &Matrix::operator=(const Matrix &rightMatrix)
{
    if (this->matrix == rightMatrix.matrix)
    {
        return *this;
    }

    if (matrix != nullptr)
    {
        delete[] matrix;
    }

    this->matrix = new double[rightMatrix.lines * rightMatrix.columns];

    this->lines = rightMatrix.lines;
    this->columns = rightMatrix.columns;

    for (int i = 0; i < lines * columns; ++i)
    {
        matrix[i] = rightMatrix.matrix[i];
    }

    return *this;
}

const Matrix operator+(const Matrix &leftMatrix, const Matrix &rightMatrix)
{
    if (!MatricesEqual(leftMatrix, rightMatrix))
    {
        return Matrix(0, 0);
    }

    Matrix newMatrix(leftMatrix.columns, leftMatrix.lines);

    for (int i = 0; i < newMatrix.lines * newMatrix.columns; ++i)
    {
        newMatrix.matrix[i] = leftMatrix.matrix[i] + rightMatrix.matrix[i];
    }

    return newMatrix;
}

const Matrix operator-(const Matrix &leftMatrix, const Matrix &rightMatrix)
{
    if (!MatricesEqual(leftMatrix, rightMatrix))
    {
        return Matrix(0, 0);
    }

    Matrix newRightMatrix = rightMatrix;
    newRightMatrix = newRightMatrix * -1;

    return leftMatrix + newRightMatrix;
}

const Matrix operator*(const Matrix &matrix, double scalarValue)
{
    Matrix newMatrix(matrix.columns, matrix.lines);

    for (int i = 0; i < newMatrix.lines * newMatrix.columns; ++i)
    {
        newMatrix.matrix[i] *= scalarValue;
    }

    return newMatrix;
}

const Matrix operator*(double scalarValue, const Matrix& matrix)
{
    return matrix * scalarValue;
}
