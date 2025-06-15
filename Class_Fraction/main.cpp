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
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "Constructor:\t\t" << this << endl;
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
	return (double)left.get_numerator() / left.get_denominator() < (double)right.get_numerator() / right.get_denominator();
}
bool operator>(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
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

std::istream& operator>>(std::istream& is, Fraction& obj)
{
	char div = '/';
	int numerator = 0, denominator = 1;
	is >> numerator >> div >> denominator;
	obj.set_integer(0);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);
	(obj.reduct()).to_proper();
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ASSIGMENT_CHECK
//#define ARITHMETICAL_OPERATORS
//#define INCREMENT_DECREMENT
//#define COMPARISON_OPERATORS
#define OUTPUT_INPUT_CHECK

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

#ifdef OUTPUT_INPUT_CHECK
	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;
#endif // OUTPUT_INPUT_CHECK

}