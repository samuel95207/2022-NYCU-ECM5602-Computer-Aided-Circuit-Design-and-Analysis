#include <iostream>
#include <vector>

using namespace std;

class Matrix {
   private:
    int row;
    int col;
    double** data;

   public:
    // Constructors and destructor
    Matrix();
    Matrix(int row, int col);
    Matrix(int row, int col, double** arr2D);
    Matrix(const initializer_list<initializer_list<double>>& arr2D);
    Matrix(const Matrix& matrix);
    ~Matrix();

    // Setters and Getters
    void fill(double value);
    void clear();
    bool setValue(int rowIdx, int colIdx, double value);
    bool setIdentity();
    double getValue(int rowIdx, int colIdx) const;
    pair<int, int> getSize() const;
    bool isSquare() const;
    bool isValid() const;
    void print() const;


    // Matrix algorithms
    Matrix transpose() const;
    Matrix cofactor(int rowCut, int colCut) const;
    double determinant() const;
    Matrix adjoint() const;
    Matrix inverse() const;
    pair<pair<Matrix, Matrix>, Matrix> LUDecomposition() const;
    static Matrix solveEquation(const Matrix& coefficientMatrix, const Matrix& resultMatrix,
                                string method = "LUDecomposition");
    bool stamp(const Matrix& matrix, const vector<int>& rowOffsets, const vector<int>& colOffsets);
    bool swapRow(int row1, int row2);
    bool swapCol(int col1, int col2);


   private:
    static Matrix _solveEquationUsingInv(const Matrix& coefficientMatrix, const Matrix& resultMatrix);
    static Matrix _solveEquationUsingLUDecomposition(const Matrix& coefficientMatrix, const Matrix& resultMatrix);



    // Operatr overloads
   public:
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
    friend ostream& operator<<(std::ostream& out, const Matrix& element);
};