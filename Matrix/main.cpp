#include "Headers/Matrix.h"

int main()
{
    // Print Matrix
    /*Matrix matrix1(5, 5);
    matrix1.PrintMatrix();*/

    // Get/Set values
    /*cout << endl;

    Matrix matrix2(5, 5);

    cout << matrix2.GetValue(3, 3) << endl;

    double value = 45;
    matrix2.SetValue(3, 3, value);

    matrix2.PrintMatrix();*/

    // Copy Matrix
    Matrix matrix3(5, 5);
    Matrix matrix4(1, 1);

    matrix4 = matrix3;

    matrix4.PrintMatrix();
}
