#include "Matrix.h"

#include <iostream>

using namespace std;

Matrix::Matrix() : row(0), col(0) { data = nullptr; }
Matrix::Matrix(int row, int col) : row(row), col(col) {
    // if (row <= 0 || col <= 0) {
    //     row = 0;
    //     col = 0;
    // }
    data = new double*[row];
    for (int i = 0; i < row; i++) {
        double* rowArr = new double[col];
        for (int j = 0; j < col; j++) {
            rowArr[j] = 0;
        }
        data[i] = rowArr;
    }
}

Matrix::Matrix(int row, int col, double** arr2D) : row(row), col(col) {
    data = new double*[row];
    for (int i = 0; i < row; i++) {
        double* rowArr = new double[col];
        for (int j = 0; j < col; j++) {
            rowArr[j] = arr2D[i][j];
        }
        data[i] = rowArr;
    }
}

Matrix::Matrix(const initializer_list<initializer_list<double>>& arr2D) {
    row = arr2D.size();
    col = arr2D.begin()[0].size();

    data = new double*[row];
    for (int i = 0; i < row; i++) {
        double* rowArr = new double[col];
        for (int j = 0; j < col; j++) {
            rowArr[j] = (arr2D.begin()[i]).begin()[j];
        }
        data[i] = rowArr;
    }
}



Matrix::Matrix(const Matrix& matrix) {
    row = matrix.row;
    col = matrix.col;

    data = new double*[row];
    for (int i = 0; i < row; i++) {
        double* rowArr = new double[col];
        for (int j = 0; j < col; j++) {
            rowArr[j] = matrix.data[i][j];
        }
        data[i] = rowArr;
    }
}


Matrix::~Matrix() {
    for (int i = 0; i < row; i++) {
        delete[] data[i];
    }
    delete[] data;
}

void Matrix::fill(double value) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] = value;
        }
    }
}

void Matrix::clear() { fill(0); }

void Matrix::setValue(int rowIdx, int colIdx, double value) {
    if (rowIdx >= row || rowIdx < 0) {
        cerr << "Error! Row index out of bound\n";
        return;
    }
    if (colIdx >= col || colIdx < 0) {
        cerr << "Error! Col index out of bound\n";
        return;
    }
    data[rowIdx][colIdx] = value;
}

double Matrix::getValue(int rowIdx, int colIdx) {
    if (rowIdx >= row || rowIdx < 0) {
        cerr << "Error! Row index out of bound\n";
        return 0;
    }
    if (colIdx >= col || colIdx < 0) {
        cerr << "Error! Col index out of bound\n";
        return 0;
    }
    return data[rowIdx][colIdx];
}

pair<int, int> Matrix::getSize() { return pair<int, int>(row, col); }


void Matrix::print() {
    cout << "[ ";
    for (int i = 0; i < row; i++) {
        if (i != 0) {
            cout << "  ";
        }
        for (int j = 0; j < col; j++) {
            cout << data[i][j] << " ";
        }
        if (i != row - 1) {
            cout << "\n";
        }
    }
    cout << "]\n";
}


Matrix& Matrix::operator=(const Matrix& matrix) {
    if (data != nullptr) {
        for (int i = 0; i < row; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    row = matrix.row;
    col = matrix.col;

    data = new double*[row];
    for (int i = 0; i < row; i++) {
        double* rowArr = new double[col];
        for (int j = 0; j < col; j++) {
            rowArr[j] = matrix.data[i][j];
        }
        data[i] = rowArr;
    }

    return *this;
}

Matrix& Matrix::operator=(const initializer_list<initializer_list<double>>& arr2D) {
    if (data != nullptr) {
        for (int i = 0; i < row; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    row = arr2D.size();
    col = arr2D.begin()[0].size();

    data = new double*[row];
    for (int i = 0; i < row; i++) {
        double* rowArr = new double[col];
        for (int j = 0; j < col; j++) {
            rowArr[j] = (arr2D.begin()[i]).begin()[j];
        }
        data[i] = rowArr;
    }

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix) {
    if (row != matrix.row || col != matrix.col) {
        return *this;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] += matrix.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix) {
    if (row != matrix.row || col != matrix.col) {
        return *this;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] -= matrix.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix) {
    if (row != matrix.row || col != matrix.col) {
        return *this;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] *= matrix.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(const Matrix& matrix) {
    if (row != matrix.row || col != matrix.col) {
        return *this;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] /= matrix.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const double& d) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] *= d;
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(const double& d) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] /= d;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& matrix) const {
    if (row != matrix.row || col != matrix.col) {
        return Matrix();
    }
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = data[i][j] + matrix.data[i][j];
        }
    }

    return newMatrix;
}

Matrix Matrix::operator-(const Matrix& matrix) const {
    if (row != matrix.row || col != matrix.col) {
        return Matrix();
    }
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = data[i][j] - matrix.data[i][j];
        }
    }

    return newMatrix;
}

Matrix Matrix::operator*(const Matrix& matrix) const {
    if (row != matrix.row || col != matrix.col) {
        return Matrix();
    }
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = data[i][j] * matrix.data[i][j];
        }
    }

    return newMatrix;
}

Matrix Matrix::operator/(const Matrix& matrix) const {
    if (row != matrix.row || col != matrix.col) {
        return Matrix();
    }
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = data[i][j] / matrix.data[i][j];
        }
    }

    return newMatrix;
}


Matrix Matrix::operator*(const double& d) const {
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = data[i][j] * d;
        }
    }

    return newMatrix;
}

Matrix Matrix::operator/(const double& d) const {
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = data[i][j] / d;
        }
    }

    return newMatrix;
}

Matrix operator*(const double& d, const Matrix& matrix) { return matrix.operator*(d); }


Matrix Matrix::operator+() const {
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = data[i][j];
        }
    }

    return newMatrix;
}

Matrix Matrix::operator-() const {
    Matrix newMatrix(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[i][j] = -data[i][j];
        }
    }

    return newMatrix;
}




bool Matrix::operator==(const Matrix& matrix) const {
    if (row != matrix.row || col != matrix.col) {
        return false;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (data[i][j] != matrix.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}


bool Matrix::operator!=(const Matrix& matrix) const { return !operator==(matrix); }
