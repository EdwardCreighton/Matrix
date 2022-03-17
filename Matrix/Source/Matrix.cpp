#include "../Headers/Matrix.h"

Matrix::Matrix(int columns, int lines)
{
    this->lines = lines;
    this->columns = columns;

    int length = columns * lines;

    matrix = new double[length];

    SimpleInitMatrix();
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

void Matrix::SetValue(int columnIndex, int lineIndex, double &value)
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
