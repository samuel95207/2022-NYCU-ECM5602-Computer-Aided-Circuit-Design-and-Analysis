#include <iostream>

using namespace std;

class Matrix {
   private:
    int row;
    int col;
    double** data;

   public:
    Matrix();
    Matrix(int row, int col);
    Matrix(int row, int col, double** arr2D);
    Matrix(const initializer_list<initializer_list<double>>& arr2D);
    Matrix(const Matrix& matrix);
    ~Matrix();

    void fill(double value);
    void clear();
    void setValue(int rowIdx, int colIdx, double value);
    double getValue(int rowIdx, int colIdx);
    pair<int, int> getSize();
    void print();

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(const initializer_list<initializer_list<double>>& arr2D);
    Matrix& operator+=(const Matrix& matrix);
    Matrix& operator-=(const Matrix& matrix);
    Matrix& operator*=(const Matrix& matrix);
    Matrix& operator/=(const Matrix& matrix);
    Matrix& operator*=(const double& d);
    Matrix& operator/=(const double& d);
    Matrix& operator&=(const Matrix& matrix);
    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Matrix& matrix) const;
    Matrix operator/(const Matrix& matrix) const;
    Matrix operator*(const double& d) const;
    Matrix operator/(const double& d) const;
    Matrix operator&(const Matrix& matrix) const;
    friend Matrix operator*(const double& d, const Matrix& matrix);
    Matrix operator-() const;
    Matrix operator+() const;
    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;
};