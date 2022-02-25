#include "Matrix.h"

#include <iomanip>
#include <iostream>
#include <vector>

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

bool Matrix::setValue(int rowIdx, int colIdx, double value) {
    if (rowIdx >= row || rowIdx < 0) {
        cerr << "Error! Row index out of bound\n";
        return false;
        ;
    }
    if (colIdx >= col || colIdx < 0) {
        cerr << "Error! Col index out of bound\n";
        return false;
    }
    data[rowIdx][colIdx] = value;
    return true;
}

bool Matrix::setIdentity() {
    if (!isSquare()) {
        return false;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j) {
                data[i][j] = 1;
            } else {
                data[i][j] = 0;
            }
        }
    }

    return true;
}

double Matrix::getValue(int rowIdx, int colIdx) const {
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

pair<int, int> Matrix::getSize() const { return pair<int, int>(row, col); }



bool Matrix::isSquare() const { return row == col && isValid(); }

bool Matrix::isValid() const { return row > 0 && col > 0; }


void Matrix::print() const {
    for (int i = 0; i < row; i++) {
        cout << "|\t";
        for (int j = 0; j < col; j++) {
            cout << setprecision(3) << data[i][j] << "\t";
        }
        cout << "|\n";
    }
}


Matrix Matrix::transpose() const {
    Matrix newMatrix(col, row);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix.data[j][i] = data[i][j];
        }
    }

    return newMatrix;
}



Matrix Matrix::cofactor(int rowCut, int colCut) const {
    if (!isSquare()) {
        cerr << "Error! Matrix is not square.\n";
        return Matrix();
    }
    Matrix newMatrix(row - 1, col - 1);
    int newRowIdx = 0, newColIdx = 0;

    for (int rowIdx = 0; rowIdx < row; rowIdx++) {
        for (int colIdx = 0; colIdx < col; colIdx++) {
            if (rowIdx != rowCut && colIdx != colCut) {
                newMatrix.data[newRowIdx][newColIdx] = data[rowIdx][colIdx];

                newColIdx++;
                if (newColIdx == newMatrix.row) {
                    newColIdx = 0;
                    newRowIdx++;
                }
            }
        }
    }

    return newMatrix;
}


double Matrix::determinant() const {
    if (!isSquare()) {
        cerr << "Error! Matrix is not square.\n";
        return 0.0;
    }

    if (row == 1) {
        return data[0][0];
    }

    double det = 0.0;
    int sign = 1;

    for (int i = 0; i < row; i++) {
        det += sign * data[0][i] * cofactor(0, i).determinant();
        sign = -sign;
    }

    return det;
}


Matrix Matrix::adjoint() const {
    if (!isSquare()) {
        cerr << "Error! Matrix is not square.\n";
        return Matrix();
    }

    Matrix newMatrix(row, col);

    if (row == 1) {
        newMatrix.data[0][0] = 1;
        return newMatrix;
    }

    int sign = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            newMatrix.data[j][i] = sign * cofactor(i, j).determinant();
        }
    }

    return newMatrix;
}

Matrix Matrix::inverse() const {
    if (!isSquare()) {
        cerr << "Error! Matrix is not square.\n";
        return Matrix();
    }

    float det = determinant();
    if (det == 0.0) {
        cerr << "Error! Singular Matrix, inverse does not exist.";
        return Matrix();
    }

    return adjoint() / det;
}


Matrix Matrix::solveEquation(const Matrix& coefficientMatrix, const Matrix& resultMatrix) {
    Matrix inv = coefficientMatrix.inverse();
    if (!inv.isValid()) {
        return Matrix();
    }
    if (coefficientMatrix.col != resultMatrix.row) {
        if (coefficientMatrix.col != resultMatrix.col) {
            cerr << "Error! dimention error.\n";
            return Matrix();
        }
        return inv & resultMatrix.transpose();
    }

    return inv & resultMatrix;
}



bool Matrix::stamp(const Matrix& matrix, const vector<int>& rowOffsets, const vector<int>& colOffsets) {
    if (matrix.row > row) {
        cerr << "Error! stamping matrix row out of bound.\n";
        return false;
    }
    if (matrix.col > col) {
        cerr << "Error! stamping matrix col out of bound.\n";
        return false;
    }

    int rowOffsetsSize = rowOffsets.size();
    int colOffsetsSize = colOffsets.size();

    if (matrix.row != rowOffsetsSize) {
        cerr << "Error! stamping matrix row != rowOffsets.size().\n";
        return false;
    }
    if (matrix.col != colOffsetsSize) {
        cerr << "Error! stamping matrix col != colOffsets.size().\n";
        return false;
    }

    for (int i = 0; i < rowOffsetsSize; i++) {
        for (int j = 0; j < colOffsetsSize; j++) {
            int rowOffset = rowOffsets[i];
            int colOffset = colOffsets[j];

            if (rowOffset > row || rowOffset < 0) {
                cerr << "Error! stamping matrix rowOffset out of bound.\n";
                return false;
            }
            if (colOffset > col || colOffset < 0) {
                cerr << "Error! stamping matrix colOffset out of bound.\n";
                return false;
            }
            data[rowOffset][colOffset] += matrix.data[i][j];
        }
    }

    return true;
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
        cerr << "Error! dimention error.\n";
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
        cerr << "Error! dimention error.\n";
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
        cerr << "Error! dimention error.\n";
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
        cerr << "Error! dimention error.\n";
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

Matrix& Matrix::operator&=(const Matrix& matrix) {
    if (col != matrix.row) {
        cerr << "Error! dimention error.\n";
        return *this;
    }

    *this = this->operator&(matrix);

    return *this;
}

Matrix Matrix::operator+(const Matrix& matrix) const {
    if (row != matrix.row || col != matrix.col) {
        cerr << "Error! dimention error.\n";
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
        cerr << "Error! dimention error.\n";
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
        cerr << "Error! dimention error.\n";
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
        cerr << "Error! dimention error.\n";
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

Matrix Matrix::operator&(const Matrix& matrix) const {
    if (col != matrix.row) {
        cerr << "Error! dimention error.\n";
        return Matrix();
    }

    Matrix newMatrix(row, matrix.col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < matrix.col; j++) {
            double sum = 0.0;
            for (int k = 0; k < col; k++) {
                sum += data[i][k] * matrix.data[k][j];
            }
            newMatrix.data[i][j] = sum;
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


ostream& operator<<(ostream& out, const Matrix& matrix) {
    for (int i = 0; i < matrix.row; i++) {
        for (int j = 0; j < matrix.col; j++) {
            out << matrix.data[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}
