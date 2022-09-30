#include "../Headers/Matrix.h"

int Matrix::error = 0;
const double Matrix::FloatEps = 1e-15;

Matrix::Matrix()
{
    this->lines = 0;
    this->columns = 0;
    linLength = 0;
    pMatrix = nullptr;
}

Matrix::Matrix(unsigned int lines, unsigned int columns)
{
    if (lines == 0)
    {
        this->lines = 0;
        this->columns = 0;
        linLength = 0;
        pMatrix = nullptr;

        return;
    }

    if (columns == 0)
    {
        columns = lines;
    }

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

void Matrix::ChD(const Matrix& matrixA, Matrix& matrixL, Matrix& matrixU)
{
    unsigned int size = matrixL.lines;
    double value;
    double sum;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            sum = 0.0;
            for (int k = 0; k < j; ++k)
            {
                sum += matrixL.GetValue(i, k) * matrixL.GetValue(j, k);
            }

            value = (matrixA.GetValue(i, j) - sum) / matrixL.GetValue(j, j);
            matrixL.SetValue(i, j, value);
        }

        sum = matrixA.GetValue(i, i);
        for (int k = 0; k < i; ++k)
        {
            sum -= matrixL.GetValue(i, k) * matrixL.GetValue(i, k);
        }

        value = sqrt(sum);
        matrixL.SetValue(i, i, value);
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrixU.SetValue(i, j, matrixL.GetValue(j, i));
        }
    }
}

void Matrix::GivensRotation(double current, double upper, double &c, double &s)
{
    if (abs(upper) < FloatEps)
    {
        c = 0;
        s = 1;
    }
    else
    {
        double radius = sqrt(current * current + upper * upper);
        c = upper / radius;
        s = -current / radius;
    }
}

void Matrix::InitZeros()
{
    for (int linIndex = 0; linIndex < linLength; ++linIndex)
    {
        pMatrix[linIndex] = 0;
    }
}

void Matrix::ResizeMatrix(unsigned int newLines, unsigned int newColumns)
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

void Matrix::SetValue(unsigned int lineIndex, unsigned int columnIndex, double value)
{
    if (linLength == 0)
    {
        error = -4;
        return;
    }

    pMatrix[GetArrayIndex(ClampValue(lineIndex, lines - 1),
                          ClampValue(columnIndex, columns - 1))]
            = value;
}

void Matrix::SetValues(const string& values)
{
    if (values == " " || values.empty()) return;

    basic_istringstream<char> stream;
    stream.str(values);

    int counter = 0;
    for (string line; getline(stream, line, ' ');)
    {
        pMatrix[counter] = stod(line);
        ++counter;

        if (counter == linLength) return;
    }
}

double Matrix::GetValue(unsigned int lineIndex, unsigned int columnIndex) const
{
    if (linLength == 0)
    {
        error = -4;
        return 0.0;
    }

    return pMatrix[GetArrayIndex(ClampValue(lineIndex, lines - 1),
                                 ClampValue(columnIndex, columns - 1))];
}

Matrix Matrix::Transpose() const
{
    Matrix T(columns, lines);

    for (int k = 0; k < T.lines; ++k)
    {
        for (int l = 0; l < T.columns; ++l)
        {
            T.SetValue(k, l, GetValue(l, k));
        }
    }

    return T;
}

void Matrix::LU(Matrix &matrixL, Matrix &matrixU) const
{
    if (!MatricesEqual(*this, matrixL) || !MatricesEqual(*this, matrixU))
    {
        error = -3;
        return;
    }

    if (lines != columns)
    {
        error = -10;
        return;
    }

    // Init triangular matrices
    for (int lineIndex = 0; lineIndex < lines; ++lineIndex)
    {
        for (int columnIndex = 0; columnIndex < lines; ++columnIndex)
        {
            matrixU.SetValue(lineIndex, columnIndex, 0.0);

            if (lineIndex == columnIndex)
            {
                matrixL.SetValue(lineIndex, columnIndex, 1.0);
            }
            else
            {
                matrixL.SetValue(lineIndex, columnIndex, 0.0);
            }
        }
    }

    double sum;
    double value;

    for (int lineIndex = 0; lineIndex < lines; ++lineIndex)
    {
        for (int columnIndex = 0; columnIndex < lines; ++columnIndex)
        {
            sum = 0.0;

            if (lineIndex <= columnIndex)
            {
                for (int k = 0; k < lineIndex; ++k)
                {
                    sum += matrixL.GetValue(lineIndex, k) * matrixU.GetValue(k, columnIndex);
                }

                value = GetValue(lineIndex, columnIndex) - sum;
                matrixU.SetValue(lineIndex, columnIndex, value);
            }
            else
            {
                for (int k = 0; k < columnIndex; ++k)
                {
                    sum += matrixL.GetValue(lineIndex, k) * matrixU.GetValue(k, columnIndex);
                }

                value = (GetValue(lineIndex, columnIndex) - sum) / matrixU.GetValue(columnIndex, columnIndex);
                matrixL.SetValue(lineIndex, columnIndex, value);
            }
        }
    }
}


double Matrix::DetLU() const
{
    if (this->lines != this->columns)
    {
        error = -10;
        return 0.0;
    }

    Matrix matrixL(lines);
    Matrix matrixU(lines);

    LU(matrixL, matrixU);

    double det = matrixU.pMatrix[0];

    for (int i = 1; i < matrixU.lines; ++i)
    {
        det *= matrixU(i, i);
    }

    return det;
}

double Matrix::DetLU(const Matrix &upTriMatrix)
{
    if (upTriMatrix.lines != upTriMatrix.columns)
    {
        error = -10;
        return 0.0;
    }

    double det = upTriMatrix.pMatrix[0];

    for (int i = 1; i < upTriMatrix.lines; ++i)
    {
        det *= upTriMatrix(i, i);
    }

    return det;
}

Matrix Matrix::SolveLU(const Matrix &matrixF, double *pDet) const
{
    if (lines != columns)
    {
        error = -10;
        return Matrix();
    }

    unsigned int size = lines;

    Matrix matrixL(size);
    Matrix matrixU(size);

    LU(matrixL, matrixU);

    if (pDet != nullptr)
    {
        *pDet = DetLU(matrixU);
    }

    Matrix matrixY(size, 1);
    double sum;

    for (int i = 0; i < size; ++i)
    {
        sum = 0.0;
        for (int j = 0; j < i; ++j)
        {
            sum += matrixL.GetValue(i, j) * matrixY.pMatrix[j];
        }
        
        matrixY.pMatrix[i] = matrixF.pMatrix[i] - sum;
    }

    Matrix matrixX(size, 1);

    for (int i = size - 1; i >= 0; --i)
    {
        sum = 0.0;
        for (int j = i + 1; j < size; ++j)
        {
            sum += matrixU.GetValue(i, j) * matrixX.pMatrix[j];
        }

        matrixX.pMatrix[i] = (matrixY.pMatrix[i] - sum) / matrixU.GetValue(i, i);
    }

    return matrixX;
}

Matrix Matrix::InvLU(double *pDet) const
{
    if (this->lines != this->columns)
    {
        error = -10;
        return Matrix();
    }

    Matrix invertibleMatrix(this->lines);

    for (int column = 0; column < this->lines; ++column)
    {
        Matrix columnMatrix(this->lines, 1);
        columnMatrix.pMatrix[column] = 1;

        columnMatrix = SolveLU(columnMatrix);

        for (int lineIndex = 0; lineIndex < this->lines; ++lineIndex)
        {
            invertibleMatrix.SetValue(lineIndex, column, columnMatrix.pMatrix[lineIndex]);
        }
    }

    if (pDet != nullptr)
    {
        *pDet = invertibleMatrix.DetLU();
    }

    return invertibleMatrix;
}

void Matrix::QR_Givens(Matrix &matrixQ, Matrix &matrixR) const
{
    if (!MatricesEqual(*this, matrixQ) || !MatricesEqual(*this, matrixR))
    {
        error = -3;
        return;
    }

    if (lines != columns)
    {
        error = -10;
        return;
    }

    unsigned int size = lines;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i == j) matrixQ.SetValue(i, j, 1.0);
            else matrixQ.SetValue(i, j, 0.0);
        }
    }

    for (int i = 0; i < linLength; ++i)
    {
        matrixR.pMatrix[i] = pMatrix[i];
    }

    for (int column = 0; column < size; ++column)
    {
        for (int line = size - 1; line > column; --line)
        {
            if (abs(matrixR(line, column)) < FloatEps)
            {
                continue;
            }

            Matrix matrixG(size);
            for (int i = 0; i < size; ++i)
            {
                matrixG.SetValue(i, i, 1.0);
            }

            double cos;
            double sin;
            GivensRotation(matrixR(line, column), matrixR(line - 1, column), cos, sin);

            int i = line -1;
            int j = line;

            matrixG(i, i, cos);
            matrixG(i, j, sin);
            matrixG(j, i, -sin);
            matrixG(j, j, cos);

            Matrix matrixQInitValues(matrixQ.lines, 2);

            for (int line = 0; line < matrixQ.lines; ++line)
            {
                for (int columnInit = 0, column = i; column <= j; ++column, ++columnInit)
                {
                    matrixQInitValues.SetValue(line, columnInit, matrixQ(line, column));
                }
            }

            // matrixQ = matrixQ * matrixG
            for (int line = 0; line < matrixQ.lines; ++line)
            {
                double value = matrixQInitValues(line, 0) * matrixG(i, i) + matrixQInitValues(line, 1) * matrixG(j, i);
                matrixQ(line, i, value);

                value = matrixQInitValues(line, 0) * matrixG(i, j) + matrixQInitValues(line, 1) * matrixG(j, j);
                matrixQ(line, j, value);
            }

            matrixR = matrixG.Transpose() * matrixR;
        }
    }
}

double Matrix::DetQR() const
{
    if (this->lines != this->columns)
    {
        error = -10;
        return 0.0;
    }

    Matrix matrixQ(lines);
    Matrix matrixR(lines);

    QR_Givens(matrixQ, matrixR);

    double det = matrixR.pMatrix[0];

    for (int i = 1; i < matrixR.lines; ++i)
    {
        det *= matrixR(i, i);
    }

    return det;
}

double Matrix::DetQR(const Matrix &rightTriMatrix)
{
    if (rightTriMatrix.lines != rightTriMatrix.columns)
    {
        error = -10;
        return 0.0;
    }

    double det = rightTriMatrix.pMatrix[0];

    for (int i = 1; i < rightTriMatrix.lines; ++i)
    {
        det *= rightTriMatrix(i, i);
    }

    return det;
}

Matrix Matrix::SolveQR(const Matrix &matrixF, double *pDet) const
{
    if (lines != columns)
    {
        error = -10;
        return Matrix();
    }

    unsigned int size = lines;

    Matrix matrixQ(size);
    Matrix matrixR(size);

    QR_Givens(matrixQ, matrixR);

    if (pDet != nullptr)
    {
        *pDet = DetQR(matrixR);
    }

    Matrix matrixY = matrixQ.Transpose() * matrixF;

    Matrix matrixX(size, 1);
    double sum;

    for (int line = size - 1; line >= 0; --line)
    {
        sum = 0.0;
        for (int j = line; j < size; ++j)
        {
            sum += matrixR(line, j) * matrixX.pMatrix[j];
        }

        matrixX.pMatrix[line] = (matrixY.pMatrix[line] - sum) / matrixR(line, line);
    }

    return matrixX;
}

Matrix Matrix::InvQR(double *pDet) const
{
    if (this->lines != this->columns)
    {
        error = -10;
        return Matrix();
    }

    Matrix invertibleMatrix(this->lines);

    for (int column = 0; column < this->lines; ++column)
    {
        Matrix columnMatrix(this->lines, 1);
        columnMatrix.pMatrix[column] = 1;

        columnMatrix = SolveQR(columnMatrix);

        for (int lineIndex = 0; lineIndex < this->lines; ++lineIndex)
        {
            invertibleMatrix(lineIndex, column) = columnMatrix.pMatrix[lineIndex];
        }
    }

    if (pDet != nullptr)
    {
        *pDet = invertibleMatrix.DetQR();
    }

    return invertibleMatrix;
}

Matrix &Matrix::operator=(const Matrix &rightMatrix)
{
    if (!MatricesEqual(*this, rightMatrix))
    {
        if (pMatrix != nullptr)
        {
            delete[] pMatrix;
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
    }

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
    if (!MatricesEqual(*this, otherMatrix))
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
    if (!MatricesEqual(*this, otherMatrix))
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
    for (int i = 0; i < linLength; ++i)
    {
        pMatrix[i] = pMatrix[i] * value;
    }

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &otherMatrix)
{
    if (this->columns != otherMatrix.lines)
    {
        error = -11;
        return *this;
    }

    Matrix dotProduct = (*this) * otherMatrix;

    ResizeMatrix(dotProduct.lines, dotProduct.columns);

    for (int i = 0; i < this->linLength; ++i)
    {
        this->pMatrix[i] = dotProduct.pMatrix[i];
    }

    return *this;
}

Matrix &Matrix::operator/=(double value)
{
    for (int i = 0; i < linLength; ++i)
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
            if (abs(matrix(lineIndex, columnIndex)) < Matrix::FloatEps)
            {
                os << 0.0 << "\t";
            }
            else
            {
                os << matrix(lineIndex, columnIndex) << "\t";
            }
        }

        os << endl;
    }

    return os;
}

Matrix operator+(const Matrix &leftMatrix, const Matrix &rightMatrix)
{
    if (!Matrix::MatricesEqual(leftMatrix, rightMatrix))
    {
        Matrix::error = -3;
        return Matrix();
    }

    Matrix newMatrix(leftMatrix.lines, leftMatrix.columns);

    for (int i = 0; i < newMatrix.linLength; ++i)
    {
        newMatrix.pMatrix[i] = leftMatrix.pMatrix[i] + rightMatrix.pMatrix[i];
    }

    return newMatrix;
}

Matrix operator-(const Matrix &leftMatrix, const Matrix &rightMatrix)
{
    if (!Matrix::MatricesEqual(leftMatrix, rightMatrix))
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

    for (int i = 0; i < newMatrix.linLength; ++i)
    {
        newMatrix.pMatrix[i] = matrix.pMatrix[i] * scalarValue;
    }

    return newMatrix;
}

Matrix operator*(double scalarValue, const Matrix &matrix)
{
    return matrix * scalarValue;
}

Matrix operator*(const Matrix &matrixLeft, const Matrix &matrixRight)
{
    if (matrixLeft.columns != matrixRight.lines)
    {
        Matrix::error = -11;
        return Matrix();
    }

    Matrix dotProduct(matrixLeft.lines, matrixRight.columns);
    double value;

    for (int lineIndex = 0; lineIndex < dotProduct.lines; ++lineIndex)
    {
        for (int columnIndex = 0; columnIndex < dotProduct.columns; ++columnIndex)
        {
            value = 0.0;

            for (int i = 0; i < matrixLeft.columns; ++i)
            {
                value += matrixLeft.GetValue(lineIndex, i) * matrixRight.GetValue(i, columnIndex);
            }

            dotProduct.SetValue(lineIndex, columnIndex, value);
        }
    }

    return dotProduct;
}

Matrix operator/(const Matrix &matrix, double scalarValue)
{
    Matrix newMatrix(matrix.columns, matrix.lines);

    for (unsigned int i = 0; i < newMatrix.linLength; ++i)
    {
        newMatrix.pMatrix[i] /= scalarValue;
    }

    return newMatrix;
}
