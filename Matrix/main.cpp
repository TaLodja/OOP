#include "Matrix.h"
using std::cout;
using std::endl;

void main()
{
	setlocale(LC_ALL, "");
	Matrix A(3, 3);
	A.FillRand();
	A.print();

	cout << delimiter << endl;

	cout << A.determinant() << endl;

	//cout << A.inverse() << endl;

	//cout << A.transpose() << endl;
	Matrix B(3, 3);
	B.FillRand();
	B.print();

	cout << delimiter << endl;
	Matrix C = A * B;
	cout << C << endl;

	cout << delimiter << endl;
	Matrix D;
	D = A;
	cout << D << endl;

	cout << delimiter << endl;
	Matrix E;
	E = A * 5;
	cout << E << endl;

	cout << delimiter << endl;
	Matrix F = A;
	cout << F << endl;

	cout << delimiter << endl;
	Matrix G = A / B;
	cout << G << endl;
}