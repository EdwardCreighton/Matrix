#include "../Headers/Matrix.h"

int Matrix::error = 0;
const double Matrix::FloatEps = 1e-13;

Matrix::Matrix(unsigned int lines, unsigned int columns)
{
    if (lines != 0 && columns == 0)
    {
        columns = lines;
    }

    if (lines == 0 || columns == 0)
    {
        this->lines = 0;
        this->columns = 0;
        linLength = 0;
        pMatrix = nullptr;

        return;
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

void Matrix::LUD(const Matrix &matrixA, Matrix &matrixL, Matrix &matrixU)
{
    // Init triangular matrices
    for (int lineIndex = 0; lineIndex < matrixA.lines; ++lineIndex)
    {
        for (int columnIndex = 0; columnIndex < matrixA.lines; ++columnIndex)
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

    for (int lineIndex = 0; lineIndex < matrixA.lines; ++lineIndex)
    {
        for (int columnIndex = 0; columnIndex < matrixA.lines; ++columnIndex)
        {
            sum = 0.0;

            if (lineIndex <= columnIndex)
            {
                for (int k = 0; k < lineIndex; ++k)
                {
                    sum += matrixL.GetValue(lineIndex, k) * matrixU.GetValue(k, columnIndex);
                }

                value = matrixA.GetValue(lineIndex, columnIndex) - sum;
                matrixU.SetValue(lineIndex, columnIndex, value);
            }
            else
            {
                for (int k = 0; k < columnIndex; ++k)
                {
                    sum += matrixL.GetValue(lineIndex, k) * matrixU.GetValue(k, columnIndex);
                }

                value = (matrixA.GetValue(lineIndex, columnIndex) - sum) / matrixU.GetValue(columnIndex, columnIndex);
                matrixL.SetValue(lineIndex, columnIndex, value);
            }
        }
    }
}

void Matrix::ChD(const Matrix& matrixA, Matrix& matrixL, Matrix& matrixU)
{
    double value = sqrt(matrixA.GetValue());

    matrixL.SetValue(0, 0, value);

    for (int i = 1; i < matrixL.lines; ++i)
    {
        value = matrixA.GetValue(i, 0) / matrixL.GetValue();
        matrixL.SetValue(i, 0, value);
    }
    
    double sum;

    for (int i = 1; i < matrixL.lines; ++i)
    {
        sum = 0.0;

        for (int p = 0; p < i; ++p)
        {
            sum += pow(matrixL.GetValue(i, p), 2);
        }
        
        value = sqrt(matrixA.GetValue(i, i) - sum);
        matrixL.SetValue(i, i, value);
    }

    for (int i = 1; i < matrixL.lines - 1; ++i)
    {
        for (int j = i + 1; j < matrixL.columns; ++j)
        {
            sum = 0.0;

            for (int p = 0; p < i; ++p)
            {
                sum += matrixL.GetValue(i, p) * matrixL.GetValue(j, p);
            }

            value = (1 / matrixL.GetValue(i, i)) * (matrixA.GetValue(j, i) - sum);
            matrixL.SetValue(j, i, value);
        }
    }

    for (int i = 0; i < matrixL.lines; ++i)
    {
        for (int j = 0; j < matrixL.columns; ++j)
        {
            matrixU.SetValue(i, j, matrixL.GetValue(j, i));
        }
    }
}

void Matrix::ChD2(const Matrix& matrixA, Matrix& matrixL, Matrix& matrixU)
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

void Matrix::MatrixDecomposition(const Matrix &matrixA, Matrix &matrixL, Matrix &matrixU)
{
    if (!MatricesEqual(matrixA, matrixL) || !MatricesEqual(matrixA, matrixU))
    {
        error = -3;
        return;
    }

    if (matrixA.lines != matrixA.columns)
    {
        error = -10;
        return;
    }

    if (CheckSymmetric(matrixA))
    {
        bool flag = true;

        for (int i = 0; i < matrixA.linLength; ++i)
        {
            if (matrixA.pMatrix[i] < 0.0)
            {
                flag = !flag;
                break;
            }
        }

        if (flag)
        {
            // Cholesky decomposition algorithm
            ChD2(matrixA, matrixL, matrixU);
            return;
        }
    }

    // Standard decomposition algorithm
    LUD(matrixA, matrixL, matrixU);
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
            os << matrix.pMatrix[matrix.GetArrayIndex(lineIndex, columnIndex)] << "\t";
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
