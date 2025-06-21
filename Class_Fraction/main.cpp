#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
using std::cout;

#define delimiter "\n-----------------------------------\n"

class Fraction;
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(const Fraction& left, const Fraction& right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;		//Целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0) denominator = 1;
		this->denominator = denominator;
	}

	//Constructors
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:\t\t" << this << endl;
	}
	explicit Fraction(double decimal)
	{

	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numerator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;

	}

	//Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator-()
	{
		(integer ? integer : numerator) *= (-1);
		return *this;
	}
	Fraction& operator+=(const Fraction& other)
	{
		cout << delimiter;
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//Increment/Decrement
	Fraction& operator++()		//Prefix Increment
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)	//Postfix Increment
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction& operator--()		//Prefix Decrement
	{
		integer--;
		return*this;
	}
	Fraction operator--(int)	//Postfix Decrement
	{
		Fraction old = *this;
		integer--;
		return old;
	}
	//Type-cast operators
	operator int()const
	{
		return integer + numerator / denominator;
	}
	operator double()const
	{
		return integer + (double)numerator / denominator;
	}
	//Methods
	Fraction& to_improper()		//Переводит дробь в неправильную (Целую часть интегрирует в числитель
	{
		numerator += abs(integer * denominator);
		if (integer < 0) numerator *= (-1);
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator = abs(numerator) % denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator); //swap - меняет две перемнные местами
		return inverted;
	}
	Fraction& reduct()
	{
		int gcd1 = abs(numerator), gcd2 = abs(denominator);
		if (gcd1 < gcd2) swap(gcd1, gcd2);
		while (gcd2)
		{
			gcd1 %= gcd2;
			swap(gcd1, gcd2);
		}
		numerator /= gcd1;
		denominator /= gcd1;
		return *this;
	}
	void print()const
	{
		if (integer) cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}
};

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	cout << delimiter;
	return (Fraction
		{
			left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
			left.get_denominator() * right.get_denominator()
		}.to_proper()).reduct();
}
Fraction operator-(const Fraction& left, const Fraction& right)
{
	Fraction copy = right;
	return left + (-copy);
}
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result;
	result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denominator(left.get_denominator() * right.get_denominator());*/
	/*Fraction result
	{
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	};*/
	return (Fraction
		{
			left.get_numerator() * right.get_numerator(),
			left.get_denominator() * right.get_denominator()
		}.to_proper()).reduct();
}

Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

//Comparison operators:
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() ==
		right.get_numerator() * left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj) //os - output stream
{
	if (obj.get_integer()) os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer()) os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer()) os << ")";
	}
	else if (obj.get_integer() == 0) os << 0;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj)	//is - input stream
{
	/*
	5
	1/2
	2(3/4)
	2 4/5
	3.4/5
	3,4/5
	*/
	
	const int SIZE = 32;
	char sz_input[SIZE] = {};		//sz_ - String Zero (Строка, заканчивающаяся нулем)
	//is >> sz_input;
	is.getline(sz_input, SIZE);		// Ввод строки с пробелами
	cout << sz_input << endl;
	const char delimiters[] = { '(', '/', ')', ' ', '.', ',', 0 };
	int numbers[3] = {};
	int n = 0;
	for (char* pch = strtok(sz_input, delimiters); pch && n<3; pch = strtok(NULL, delimiters))			//strtok() - разбивает строку на последовательность токенов, разделенныйх символами-разделителями
		numbers[n++] = atoi(pch);																//atoi() - преобразует строку в целое значение
	for (int i = 0; i < n; i++) cout << numbers[i] << "\t"; cout << endl;
	switch (n)
	{
	case 1:obj = Fraction(numbers[0]); break;
	case 2:obj = Fraction(numbers[0], numbers[1]); break;
	case 3: obj = Fraction(numbers[0], numbers[1], numbers[2]);break;
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ASSIGMENT_CHECK
//#define ARITHMETICAL_OPERATORS
//#define INCREMENT_DECREMENT
//#define COMPARISON_OPERATORS
//#define ISTREAM_OPERATOR
//#define CONVERSIONS_BASICS
#define CONVERTION_FROM_OTHER_TO_CLASS
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

	Fraction B;
	cout << delimiter << endl;
	B = Fraction(8);
	cout << delimiter << endl;
	cout << B << endl;

	Fraction C = 2.75;
	cout << A << endl;
#endif // CONVERTION_FROM_OTHER_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER
	Fraction A(2, 3, 4);
	cout << A << endl;

	int a = A;
	cout << a << endl;
	double b = A;
	cout << b << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

}