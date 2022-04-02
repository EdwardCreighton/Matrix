#include "Headers/Matrix.h"

int main()
{
    // Print Matrix
    /*Matrix matrix1(5);

    double value = 1;

    for (int line = 0; line < 5; ++line)
    {
        for (int column = 0; column < 5; ++column)
        {
            matrix1.SetValue(line, column, value);

            ++value;
        }
    }

    cout << matrix1 << endl;*/

    // Get/Set values
    /*Matrix matrix2(5, 5);

    cout << matrix2.GetValue(3, 3) << endl;

    double value = 45;
    matrix2.SetValue(3, 3, value);

    cout << matrix2 << endl;*/

    // Equalize Matrices
    /*Matrix matrix3(5, 5);
    Matrix matrix4(1, 1);

    matrix4 = matrix3;

    cout << matrix4 << endl;*/

    // Add Matrices
    /*Matrix matrix5(3, 3);
    Matrix matrix6(3, 3);

    double value = 1;

    for (int line = 0; line < 3; ++line)
    {
        for (int column = 0; column < 3; ++column)
        {
            matrix5.SetValue(line, column, value);
            matrix6.SetValue(line, column,value);

            ++value;
        }
    }

    Matrix matrix7 = matrix5 + matrix6;
    cout << matrix7 << endl;*/

    // Add Matrices (variant 2)
    /*Matrix matrix5(3, 3);
    Matrix matrix6(3, 3);

    double value = 1;

    for (int line = 0; line < 3; ++line)
    {
        for (int column = 0; column < 3; ++column)
        {
            matrix5.SetValue(line, column, value);
            matrix6.SetValue(line, column,value);

            ++value;
        }
    }

    matrix5 += matrix6;
    cout << matrix5 << endl;*/

    // Multiply Matrix with scalar
    /*Matrix matrix8(3, 3);

    double value = 5;

    for (int line = 0; line < 3; ++line)
    {
        for (int column = 0; column < 3; ++column)
        {
            matrix8.SetValue(line, column, value);
        }
    }

    matrix8 = matrix8 * 3;
    cout << matrix8 << endl;*/

    // Multiply Matrix with scalar (variant 2)
    /*Matrix matrix8(3, 3);

    double value = 5;

    for (int line = 0; line < 3; ++line)
    {
        for (int column = 0; column < 3; ++column)
        {
            matrix8.SetValue(line, column, value);
        }
    }

    matrix8 *= 3;
    cout << matrix8 << endl;

    matrix8 /= 5;
    cout << matrix8 << endl;*/

    // Subtract Matrices
    /*Matrix matrix9(3, 3);
    Matrix matrix10(3, 3);

    double value = 1;

    for (int line = 0; line < 3; ++line)
    {
        for (int column = 0; column < 3; ++column)
        {
            matrix9.SetValue(line, column, value);
            matrix10.SetValue(line, column, value);
            ++value;
        }
    }

    Matrix matrix11 = matrix9 - matrix10;

    cout << matrix11 << endl;*/

    // LU decomposition
    unsigned int size = 3;

    Matrix matrixA(size);

    matrixA.SetValue(0, 0, 10);
    matrixA.SetValue(0, 1, -7);
    matrixA.SetValue(0, 2, 0);
    matrixA.SetValue(1, 0, -3);
    matrixA.SetValue(1, 1, 6);
    matrixA.SetValue(1, 2, 2);
    matrixA.SetValue(2, 0, 5);
    matrixA.SetValue(2, 1, -1);
    matrixA.SetValue(2, 2, 5);

    /*matrixA.SetValue(0, 0, 4.0);
    matrixA.SetValue(0, 1, 3.0);
    matrixA.SetValue(1, 0, 6.0);
    matrixA.SetValue(1, 1, 3.0);*/

    cout << "Matrix A" << endl << matrixA << endl;

    Matrix matrixU(size);
    Matrix matrixL(size);

    Matrix::ComputeLUFactorization(matrixA, matrixL, matrixU);

    cout << "Matrix U" << endl << matrixU << endl;
    cout << "Matrix L" << endl << matrixL << endl;
}
