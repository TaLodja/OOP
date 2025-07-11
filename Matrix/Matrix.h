#pragma once
#include <iostream>

#define delimiter "\n-----------------------------------------\n"

class Matrix;
Matrix operator+(const Matrix& left, const Matrix& right);
Matrix operator*(const Matrix& obj, const int& value);
Matrix operator-(const Matrix& left, const Matrix& right);
Matrix operator*(const Matrix& obj, const int& value);
Matrix operator*(const Matrix& left, const Matrix& right);
Matrix operator/(const Matrix& left, const Matrix& right);
std::ostream& operator<<(std::ostream& os, const Matrix& obj);
double FindDet(double** arr1, int n);
double algebraic_addition(double** arr1, int r, int c, int n);

class Matrix
{
	int rows;
	int cols;
	double** matr;
public:
	int get_rows()const;
	int get_cols()const;

	//Constructors:
	Matrix(int rows = 5, int cols = 5);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	~Matrix();
	//Operators
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);
	double* operator[](int index);
	const double* operator[](int index)const;
	//Methods:
	void Allocate();
	void CopyElements(const Matrix& other);
	void Clear();
	void print()const;
	void FillRand();
	Matrix transpose() const;
	double determinant() const;
	Matrix inverse() const;
};