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

    // Add Matrices (method 2)
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

    // Multiply Matrix with scalar (method 2)
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

    // LU Decomposition
    /*unsigned int size = 3 ;

    Matrix matrixA(size);

    //string values = "10 -7 0 -3 6 2 5 -1 5 4 0 3 7 -4 9 2 -1 6 1 8 -3 2 6 2 5 -1 4 0 3 7 -1 6 1 -3 2 6 0 3 7 -1 5 4 0 9 2 -1 6 1 2 6 2 5 2 6 2 5 -1 0 3 7 -1 5 1 6 1 8 5 2 6 2 1 -3 2 -4 9 2 -1 6 6 0 3 7 -1 5 -1 6 1 8 2 5 -1 0 3 7 1 6 1 8 5 2 6 7 -1 5 -1";
    string values = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(values);

    cout << "Matrix A" << endl << matrixA << endl;

    Matrix matrixU(size);
    Matrix matrixL(size);

    //Matrix::MatrixDecomposition(matrixA, matrixL, matrixU);
    matrixA.LUDecomposition(matrixL, matrixU);

    cout << "Matrix U" << endl << matrixU << endl;
    cout << "Matrix L" << endl << matrixL << endl;

    Matrix mMatrix = matrixL * matrixU;
    cout << "Matrix Multiplication" << endl << mMatrix << endl;*/

    // Det
    /*int size = 3;
    Matrix matrixA(size);

    string values = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(values);

    // I-method
    cout << matrixA.Det() << endl;

    Matrix matrixL(size);
    Matrix matrixU(size);

    matrixA.LUDecomposition(matrixL, matrixU);

    // II-method
    cout << Matrix::Det(matrixU) << endl;*/

    // Solver
    /*unsigned int size = 3;
    Matrix matrixA(size);
    Matrix matrixF(size, 1);

    string aValues = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(aValues);
    string fValues = "1 2 3";
    matrixF.SetValues(fValues);

    double det;
    Matrix matrixX = matrixA.SolveLU(matrixF, &det);

    cout << "Det: " << det << endl;

    cout << "Matrix X" << endl << matrixX << endl;
    Matrix check = matrixA * matrixX;
    cout << "Check" << endl << check << endl;*/

    // Invertible matrix
    unsigned int size = 3;
    Matrix matrixA(size);

    string aValues = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(aValues);

    cout << "Matrix A" << endl << matrixA << endl;

    double det;

    Matrix invertibleMatrix = matrixA.InvLU(&det);
    cout << "Det Inv: " << det << endl;
    cout << "Det: " << 1 / det << endl << endl;
    cout << "Invertible Matrix" << endl << invertibleMatrix << endl;

    Matrix check = matrixA * invertibleMatrix;
    cout << "Check" << endl << check << endl;
}
