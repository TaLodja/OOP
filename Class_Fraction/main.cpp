#include "Fraction.h"
using std::cin;
using std::cout;
using std::endl;

//#define CONSTRUCTORS_CHECK
//#define ASSIGMENT_CHECK
//#define ARITHMETICAL_OPERATORS
//#define INCREMENT_DECREMENT
//#define COMPARISON_OPERATORS
//#define ISTREAM_OPERATOR
//#define CONVERSIONS_BASICS
//#define CONVERTION_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;				//DefaultConstructor
	A.print();

	Fraction B = 5;			//Single-argument constructor (Конструктор с одним параметром)
	B.print();

	Fraction C(1, 2);		//Constructor
	C.print();

	Fraction D(2, 3, 4);	//Constructor
	D.print();

	Fraction E = D;			//CopyConstructor
	E.print();

	Fraction F;				//DefaultConstructor
	F = E;					//CopyAssignment
	F.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGMENT_CHECK
	int a, b, c;

	a = b = c = 0;

	cout << a << "\t" << b << "\t" << c << endl;

	Fraction A, B, C;
	cout << delimiter;

	A = B = C = Fraction(2, 3, 4);
	//Fraction(1,3,4) явный вызов конструктора, который создает временный безымянный объект
	//Временные безымянные объекты существуют в пределах одного выражения
	cout << delimiter;
	A.print();
	B.print();
	C.print();
#endif // ASSIGMENT_CHECK

#ifdef ARITHMETICAL_OPERATORS
	Fraction A(1, 2);
	Fraction B(2, 3, 4);
	A += B;
	cout << A << endl;
	/*cout << delimiter;
	A /= B;
	A.print();
	B.print();*/
#endif // ARITHMETICAL_OPERATORS

#ifdef INCREMENT_DECREMENT
	Fraction A(1, 2);
	Fraction B = --A;
	A.print();
	B.print();
#endif // INCREMENT_DECREMENT

#ifdef COMPARISON_OPERATORS

	cout << (Fraction(1, 2) <= Fraction(5, 10)) << endl;
#endif // COMPARISON_OPERATORS

#ifdef ISTREAM_OPERATOR
	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << delimiter << endl;
	cout << A.to_proper() << endl;
#endif // ISTREAM_OPERATOR

#ifdef CONVERSIONS_BASICS
	int a = 2;		//No conversions
	double b = 3;	//Implicite Conversion from less to more ('int' to 'double')
	int c = b;		//Implicite Conversion from more to less without data loss ('double' to 'int')
	int d = 4.5;	//Implicite conversion from more to less with data loss  
#endif // CONVERSIONS_BASICS

#ifdef CONVERTION_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5;	//Implicit conversion from less to more ('int' to 'Fraction')
	cout << A << endl;

	cout << delimiter << endl;

	Fraction B;
	B = Fraction(8);
	cout << B << endl;

	cout << delimiter << endl;

	Fraction C = 0.3;
	cout << C << endl;
#endif // CONVERTION_FROM_OTHER_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER
	Fraction A(2, 3, 4);
	cout << A << endl;

	int a = A;
	cout << a << endl;
	double b = A;
	cout << b << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

	Fraction A = 2.75;
	cout << A << endl;

}