#include "Headers/Matrix.h"

int main()
{
    // Print Matrix
    /*Matrix matrix1(5);

    string values = "4 2 3 2 5 1 3 1 6";
    matrix1.SetValues(values);

    cout << matrix1 << endl;*/

    // Get/Set values
    /*Matrix matrix2(5, 5);

    //cout << matrix2.GetValue(3, 3) << endl;
    cout << matrix2(3, 3) << endl;

    double value = 45;
    //matrix2.SetValue(3, 3, value);
    matrix2(3,3) = value;

    cout << matrix2 << endl;*/

    // Equalize Matrices
    /*Matrix matrix3(5, 5);
    Matrix matrix4(1, 1);

    matrix4 = matrix3;

    cout << matrix4 << endl;*/

    // Add Matrices
    /*Matrix matrix5(3, 3);
    Matrix matrix6(3, 3);

    string values = "1 2 3 4 5 6 7 8 9";

    matrix5.SetValues(values);
    matrix6.SetValues(values);

    Matrix matrix7 = matrix5 + matrix6;
    cout << matrix7 << endl;*/

    // Add Matrices (method 2)
    /*Matrix matrix5(3, 3);
    Matrix matrix6(3, 3);

    string values = "1 2 3 4 5 6 7 8 9";

    matrix5.SetValues(values);
    matrix6.SetValues(values);

    matrix5 += matrix6;
    cout << matrix5 << endl;*/

    // Multiply Matrix with scalar
    /*Matrix matrix8(3, 3);

    string values = "1 2 3 4 5 6 7 8 9";
    matrix8.SetValues(values);

    matrix8 = matrix8 * 3;
    cout << matrix8 << endl;*/

    // Multiply Matrix with scalar (method 2)
    /*Matrix matrix8(3, 3);

    string values = "1 2 3 4 5 6 7 8 9";
    matrix8.SetValues(values);

    matrix8 *= 3;
    cout << matrix8 << endl;

    matrix8 /= 5;
    cout << matrix8 << endl;*/

    // Subtract Matrices
    /*Matrix matrix9(3, 3);
    Matrix matrix10(3, 3);

    string values = "1 2 3 4 5 6 7 8 9";

    matrix9.SetValues(values);
    matrix10.SetValues(values);

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
    matrixA.LU(matrixL, matrixU);

    cout << "Matrix U" << endl << matrixU << endl;
    cout << "Matrix L" << endl << matrixL << endl;

    Matrix mMatrix = matrixL * matrixU;
    cout << "Matrix Multiplication" << endl << mMatrix << endl;*/

    // DetLU
    /*int size = 3;
    Matrix matrixA(size);

    string values = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(values);

    // I-method
    cout << matrixA.DetLU() << endl;

    Matrix matrixL(size);
    Matrix matrixU(size);

    matrixA.LU(matrixL, matrixU);

    // II-method
    cout << Matrix::DetLU(matrixU) << endl;*/

    // Solver LU
    /*unsigned int size = 3;
    Matrix matrixA(size);
    Matrix matrixF(size, 1);

    string aValues = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(aValues);
    string fValues = "1 2 3";
    matrixF.SetValues(fValues);

    double det;
    Matrix matrixX = matrixA.SolveLU(matrixF, &det);

    cout << "DetLU: " << det << endl;

    cout << "Matrix X" << endl << matrixX << endl;
    Matrix check = matrixA * matrixX;
    cout << "Check" << endl << check << endl;*/

    // Invertible matrix LU
    /*unsigned int size = 3;
    Matrix matrixA(size);

    string aValues = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(aValues);

    cout << "Matrix A" << endl << matrixA << endl;

    double det;

    Matrix invertibleMatrix = matrixA.InvLU(&det);
    cout << "DetLU Inv: " << det << endl;
    cout << "DetLU: " << 1 / det << endl << endl;
    cout << "Invertible Matrix" << endl << invertibleMatrix << endl;

    Matrix check = matrixA * invertibleMatrix;
    cout << "Check" << endl << check << endl;*/

    //QR-Givens decomposition
    /*unsigned int size = 3;
    Matrix matrixA(size);

    string aValues = "4 2 3 2 5 1 3 1 6";
    //string aValues = "10 -7 0 -3 6 2 5 -1 5 4 0 3 7 -4 9 2 -1 6 1 8 -3 2 6 2 5 -1 4 0 3 7 -1 6 1 -3 2 6 0 3 7 -1 5 4 0 9 2 -1 6 1 2 6 2 5 2 6 2 5 -1 0 3 7 -1 5 1 6 1 8 5 2 6 2 1 -3 2 -4 9 2 -1 6 6 0 3 7 -1 5 -1 6 1 8 2 5 -1 0 3 7 1 6 1 8 5 2 6 7 -1 5 -1";
    //string aValues = "2 0 1 6 2 0 0 1 -1";
    matrixA.SetValues(aValues);

    cout << "Matrix A" << endl << matrixA << endl;

    Matrix matrixQ(size);
    Matrix matrixR(size);

    matrixA.QR_Givens(matrixQ, matrixR);
    cout << "MatrixQ" << endl << matrixQ << endl;
    cout << "MatrixR" << endl << matrixR << endl;

    Matrix check = matrixQ * matrixR;
    cout << "Check" << endl << check << endl;*/

    // DetQR
    /*int size = 3;
    Matrix matrixA(size);

    string values = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(values);

    // I-method
    cout << matrixA.DetQR() << endl;

    Matrix matrixQ(size);
    Matrix matrixR(size);

    matrixA.QR_Givens(matrixQ, matrixR);

    // II-method
    cout << Matrix::DetQR(matrixR) << endl;*/

    // Solver QR
    /*unsigned int size = 3;
    Matrix matrixA(size);
    Matrix matrixF(size, 1);

    string aValues = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(aValues);
    string fValues = "1 2 3";
    matrixF.SetValues(fValues);

    double det;
    Matrix matrixX = matrixA.SolveQR(matrixF, &det);

    cout << "DetQR: " << det << endl << endl;

    cout << "Matrix X" << endl << matrixX << endl;
    Matrix check = matrixA * matrixX;
    cout << "Check" << endl << check << endl;*/

    // Invertible matrix QR
    /*unsigned int size = 3;
    Matrix matrixA(size);

    string aValues = "4 2 3 2 5 1 3 1 6";
    matrixA.SetValues(aValues);

    cout << "Matrix A" << endl << matrixA << endl;

    double det;

    Matrix invertibleMatrix = matrixA.InvQR(&det);
    cout << "DetQR Inv: " << det << endl;
    cout << "DetQR: " << 1 / det << endl << endl;
    cout << "Invertible Matrix" << endl << invertibleMatrix << endl;

    Matrix check = matrixA * invertibleMatrix;
    cout << "Check" << endl << check << endl;*/
}
