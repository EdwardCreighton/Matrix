#include "Headers/Matrix.h"

int main()
{
    Matrix matrix1(5, 5);

    matrix1.PrintMatrix();

    cout << endl;

    cout << matrix1.GetValue(3, 3) << endl;

    double value = 45;
    matrix1.SetValue(3, 3, value);

    matrix1.PrintMatrix();
}
