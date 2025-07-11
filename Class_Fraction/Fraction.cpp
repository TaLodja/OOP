#include "Fraction.h"
using std::cin;
using std::cout;
using std::endl;

int Fraction::get_integer()const
{
	return integer;
}
int  Fraction::get_numerator()const
{
	return numerator;
}
int  Fraction::get_denominator()const
{
	return denominator;
}
void  Fraction::set_integer(int integer)
{
	this->integer = integer;
}
void  Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
}
void  Fraction::set_denominator(int denominator)
{
	if (denominator == 0) denominator = 1;
	this->denominator = denominator;
}

//Constructors
Fraction::Fraction()
{
	this->integer = 0;
	this->numerator = 0;
	this->denominator = 1;
	cout << "DefaultConstructor:\t" << this << endl;
}
Fraction::Fraction(int integer)
{
	this->integer = integer;
	this->numerator = 0;
	this->denominator = 1;
	cout << "SingleArgumentConstructor:\t\t" << this << endl;
}
Fraction::Fraction(double decimal)
{
	decimal += 1e-10;
	integer = decimal;  //Ќе€вное преобразование типов из 'double' в  'int'
	decimal -= integer;
	denominator = 1e+9; //ћаксимально возможное значение числител€ (9 дес€тичных разр€дов)
	numerator = decimal * denominator;
	reduce();
}
Fraction::Fraction(int numerator, int denominator)
{
	this->integer = 0;
	this->numerator = numerator;
	this->set_denominator(denominator);
	cout << "Constructor:\t\t" << this << endl;
}
Fraction::Fraction(int integer, int numerator, int denominator)
{
	set_integer(integer);
	set_numerator(numerator);
	set_denominator(denominator);
	cout << "Constructor:\t\t" << this << endl;
}
Fraction::Fraction(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	cout << "CopyConstructor:\t" << this << endl;
}
Fraction::~Fraction()
{
	cout << "Destructor:\t\t" << this << endl;

}

//Operators
Fraction& Fraction::operator=(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	cout << "CopyAssignment:\t\t" << this << endl;
	return *this;
}
Fraction& Fraction::operator-()
{
	(integer ? integer : numerator) *= (-1);
	return *this;
}
Fraction& Fraction::operator+=(const Fraction& other)
{
	cout << delimiter;
	return *this = *this + other;
}
Fraction& Fraction::operator-=(const Fraction& other)
{
	return *this = *this - other;
}
Fraction& Fraction::operator*=(const Fraction& other)
{
	return *this = *this * other;
}
Fraction& Fraction::operator/=(const Fraction& other)
{
	return *this = *this / other;
}

//Increment/Decrement
Fraction& Fraction::operator++()		//Prefix Increment
{
	integer++;
	return *this;
}
Fraction  Fraction::operator++(int)	//Postfix Increment
{
	Fraction old = *this;
	integer++;
	return old;
}
Fraction& Fraction::operator--()		//Prefix Decrement
{
	integer--;
	return*this;
}
Fraction  Fraction::operator--(int)	//Postfix Decrement
{
	Fraction old = *this;
	integer--;
	return old;
}
//Type-cast operators
Fraction::operator int()const
{
	return integer + numerator / denominator;
}
Fraction::operator double()const
{
	return integer + (double)numerator / denominator;
}
//Methods
Fraction& Fraction::to_improper()		//ѕереводит дробь в неправильную (÷елую часть интегрирует в числитель
{
	numerator += abs(integer * denominator);
	if (integer < 0) numerator *= (-1);
	integer = 0;
	return *this;
}
Fraction& Fraction::to_proper()
{
	integer += numerator / denominator;
	numerator = abs(numerator) % denominator;
	return *this;
}
Fraction  Fraction::inverted()const
{
	Fraction inverted = *this;
	inverted.to_improper();
	std::swap(inverted.numerator, inverted.denominator); //swap - мен€ет две перемнные местами
	return inverted;
}
Fraction& Fraction::reduce()
{
	int more, less, rest;
	if (numerator < denominator)
	{
		less = numerator;
		more = denominator;
	}
	else
	{
		more = numerator;
		less = denominator;
	}
	do
	{
		rest = more % less;
		more = less;
		less = rest;
	} while (rest);
	int GCD = more; //GCD - Greatest Common Divisor
	numerator /= GCD;
	denominator /= GCD;
	return *this;
}
void  Fraction::print()const
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

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	cout << delimiter;
	return (Fraction
		{
			left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
			left.get_denominator() * right.get_denominator()
		}.to_proper()).reduce();
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
		}.to_proper()).reduce();
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
	const int SIZE = 32;
	char sz_input[SIZE] = {};		//sz_ - String Zero (—трока, заканчивающа€с€ нулем)
	//is >> sz_input;
	is.getline(sz_input, SIZE);		// ¬вод строки с пробелами
	cout << sz_input << endl;
	const char delimiters[] = { '(', '/', ')', ' ', '.', ',', 0 };
	int numbers[3] = {};
	int n = 0;
	for (char* pch = strtok(sz_input, delimiters); pch && n < 3; pch = strtok(NULL, delimiters))			//strtok() - разбивает строку на последовательность токенов, разделенныйх символами-разделител€ми
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