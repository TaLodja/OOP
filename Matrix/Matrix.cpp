#include "Matrix.h"
using std::cout;
using std::endl;

int Matrix::get_rows()const
{
	return rows;
}
int Matrix::get_cols()const
{
	return cols;
}
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), matr(new double* [rows])
{
	Allocate();
	cout << "Constructor:\t\t" << this << endl;
}
Matrix::Matrix(const Matrix& other) :Matrix(other.rows, other.cols)
{
	CopyElements(other);
	cout << "CopyConstructor:\t" << this << endl;
}
Matrix::Matrix(Matrix&& other) : rows(other.rows), cols(other.cols), matr(other.matr)
{
	other.rows = 0;
	other.cols = 0;
	other.matr = nullptr;
	cout << "MoveConstructor:\t" << this << endl;
}
Matrix::~Matrix()
{
	Clear();
	cout << "Destructor:\t\t" << this << endl;
}
Matrix& Matrix::operator=(const Matrix& other)
{
	if (this == &other) return *this;
	Clear();
	this->rows = other.rows;
	this->cols = other.cols;
	this->matr = new double* [rows];
	Allocate();
	CopyElements(other);
	cout << "CopyAssignment\t\t" << this << endl;
	return *this;
}
Matrix& Matrix::operator=(Matrix&& other)
{
	if (this == &other) return *this;
	Clear();
	this->rows = other.rows;
	this->cols = other.cols;
	this->matr = other.matr;
	other.rows = 0;
	other.cols = 0;
	other.matr = nullptr;
	cout << "MoveAssignment\t\t" << this << endl;
	return *this;
}
double* Matrix::operator[](int index)
{
	return matr[index];
}
const double* Matrix::operator[](int index)const
{
	return matr[index];
}
void Matrix::Allocate()
{
	for (int i = 0; i < rows; i++)
	{
		this->matr[i] = new double[cols] {};
	}
}
void Matrix::CopyElements(const Matrix& other)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matr[i][j] = other.matr[i][j];
}
void Matrix::Clear()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matr[i];
	}
	delete[] matr;
	matr = nullptr;
}
void Matrix::print()const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matr[i][j] << "\t\t";
		}
		cout << endl;
	}
}
void Matrix::FillRand()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			matr[i][j] = rand() % 100;
			matr[i][j] /= 100;
		}
}
Matrix Matrix::transpose() const
{
	Matrix transposed(cols, rows);
	for (int i = 0; i < rows;i++)
		for (int j = 0; j < cols; j++)
			transposed[j][i] = matr[i][j];
	return transposed;
}
double Matrix::determinant() const
{
	if (rows != cols || rows == 0) return 0;
	return FindDet(matr, cols);
}
Matrix Matrix::inverse() const
{
	if (rows != cols || determinant() == 0) return Matrix(0, 0);
	Matrix temp(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp[i][j] = algebraic_addition(matr, i, j, cols);
	return temp.transpose() * (1 / determinant());
}
Matrix operator+(const Matrix& left, const Matrix& right)
{
	if (left.get_rows() != right.get_rows() || left.get_cols() != right.get_cols()) return Matrix(0, 0);
	Matrix result(left.get_rows(), left.get_cols());
	for (int i = 0; i < left.get_rows(); i++)
		for (int j = 0; j < left.get_cols(); j++)
			result[i][j] = left[i][j] + right[i][j];
	return result;
}
Matrix operator-(const Matrix& left, const Matrix& right)
{
	if (left.get_rows() != right.get_rows() || left.get_cols() != right.get_cols()) return Matrix(0, 0);
	Matrix result(left.get_rows(), left.get_cols());
	for (int i = 0; i < left.get_rows(); i++)
		for (int j = 0; j < left.get_cols(); j++)
			result[i][j] = left[i][j] - right[i][j];
	return result;
}
Matrix operator*(const Matrix& obj, const int& value)
{
	Matrix result(obj.get_rows(), obj.get_cols());
	for (int i = 0; i < obj.get_rows(); i++)
		for (int j = 0; j < obj.get_cols(); j++)
			result[i][j] = obj[i][j] * value;
	return result;
}
Matrix operator*(const Matrix& left, const Matrix& right)
{
	if (left.get_cols() != right.get_rows()) return Matrix(0, 0);
	Matrix result(left.get_rows(), right.get_cols());
	for (int i = 0; i < left.get_rows(); i++)
		for (int j = 0; j < right.get_cols(); j++)
			for (int k = 0; k < left.get_cols(); k++)
				result[i][j] += left[i][k] * right[k][j];
	return result;
}
Matrix operator/(const Matrix& left, const Matrix& right)
{
	return left * right.inverse();
}
std::ostream& operator<<(std::ostream& os, const Matrix& obj)
{
	for (int i = 0; i < obj.get_rows(); i++)
	{
		for (int j = 0; j < obj.get_cols(); j++)
		{
			cout << obj[i][j] << "\t\t";
		}
		os << endl;
	}
	return os;
}
double FindDet(double** arr1, int n)
{
	if (n == 1) return arr1[0][0];
	else if (n == 2) return arr1[0][0] * arr1[1][1] - arr1[0][1] * arr1[1][0];
	else
	{
		double d = 0;
		for (int k = 0; k < n; k++)
		{
			d += arr1[0][k] * algebraic_addition(arr1, 0, k, n);
		}
		return d;
	}
}
double algebraic_addition(double** arr1, int r, int c, int n)
{
	double** cofactor = new double* [n - 1];
	for (int i = 0; i < n - 1; i++)
		cofactor[i] = new double[n - 1];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == c || i == r) continue;
			else if (j < c && i < r) cofactor[i][j] = arr1[i][j];
			else if (j < c && i > r) cofactor[i - 1][j] = arr1[i][j];
			else if (j > c && i < r) cofactor[i][j - 1] = arr1[i][j];
			else cofactor[i - 1][j - 1] = arr1[i][j];
		}
	}
	double al_add = pow(-1, r + c) * FindDet(cofactor, n - 1);
	for (int i = 0; i < n - 1; i++)
		delete[] cofactor[i];
	delete[] cofactor;
	return al_add;
}