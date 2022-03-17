#include "../Headers/Matrix.h"

Matrix::Matrix(int columns, int lines)
{
    this->lines = lines;
    this->columns = columns;

    int length = columns * lines;

    matrix = new double[length];

    InitMatrix();
}

Matrix::~Matrix()
{
    delete[] matrix;
}

void Matrix::InitMatrix()
{
    for (int i = 0; i < lines * columns; ++i)
    {
        matrix[i] = (double) (i + 1);
    }
}

void Matrix::PrintMatrix()
{
    cout << matrix << endl;

    for (int columnsCount = 0; columnsCount < lines * columns; ++columnsCount)
    {
        if ((columnsCount) % columns == 0)
        {
            cout << endl;
        }

        cout << matrix[columnsCount] << "\t";
    }
}
