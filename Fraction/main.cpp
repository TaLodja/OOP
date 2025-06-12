#include <iostream>
using namespace std;

#define delimiter "\n-------------------------------\n"

class Fraction
{
	int numerator, denominator, whole;
public:
	int get_num() const
	{
		return numerator;
	}
	int get_denom() const
	{
		return denominator;
	}
	int get_whole() const
	{
		return whole;
	}
	void set_num(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denom(int denominator)
	{
		this->denominator = denominator;
	}
	void set_whole(int whole)
	{
		this->whole = whole;
	}

	//Constructor

	Fraction(int numerator = 0, int denominator = 1)
	{
		if (denominator == 0) throw "Знаменатель не может быть равен 0!"; //Бросаем исключение с сообщением об ошибке
		this->whole = 0;
		this->numerator = numerator;
		this->denominator = denominator;
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(int whole, int numerator, int denominator) //Для вывода смешанного числа
	{
		if (denominator == 0) throw "Знаменатель не может быть равен 0!";
		this->whole = whole;
		this->numerator = numerator;
		this->denominator = denominator;
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(const Fraction& other)
	{
		this->whole = other.whole;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t\t" << this << endl;
	}

	//Destructor

	~Fraction()
	{
		cout << "Destructor\t\t" << this << endl;
	}

	//Operator

	Fraction& operator=(const Fraction& other)
	{
		this->whole = other.whole;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		reduction();
		return *this;
	}
	Fraction& operator-()
	{
		(this->whole != 0) ? this->whole *= (-1) : this->numerator *= (-1);
		return *this;
	}
	Fraction& operator++()
	{
		if (this->whole != 0) incorrect_fraction();
		this->numerator += this->denominator;
		reduction();
		return *this;
	}
	Fraction& operator++(int)		//int - фиктивный целочистенный параметр для постфиксного инкремента
	{
		return ++(*this);
	}
	Fraction& operator--()
	{
		if (this->whole != 0) incorrect_fraction();
		this->numerator -= this->denominator;
		reduction();
		return *this;
	}
	Fraction& operator--(int)		//int - фиктивный целочистенный параметр для постфиксного декремента
	{
		return --(*this);
	}
	Fraction operator+=(Fraction& right)
	{
		if (this->whole != 0) incorrect_fraction();
		if (right.whole != 0) right.incorrect_fraction();
		this->numerator = this->numerator * right.denominator + right.numerator * this->denominator;
		this->denominator *= right.denominator;
		reduction();
		return *this;
	}
	Fraction operator-=(Fraction& right)
	{
		if (this->whole != 0) incorrect_fraction();
		if (right.whole != 0) right.incorrect_fraction();
		this->numerator = this->numerator * right.denominator - right.numerator * this->denominator;
		this->denominator *= right.denominator;
		reduction();
		return *this;
	}
	Fraction operator*=(Fraction& right)
	{
		if (this->whole != 0) incorrect_fraction();
		if (right.whole != 0) right.incorrect_fraction();
		this->numerator *= right.numerator;
		this->denominator *= right.denominator;
		reduction();
		return *this;
	}
	Fraction operator/=(Fraction& right)
	{
		if (this->whole != 0) incorrect_fraction();
		if (right.whole != 0) right.incorrect_fraction();
		this->numerator *= right.denominator;
		this->denominator *= right.numerator;
		reduction();
		return *this;
	}

	//Method

	void print()					//Вывод дроби на экран
	{
		reduction();
		if (abs(this->numerator) >= abs(this->denominator)) mixed_number();
		(this->whole == 0 && this->numerator == 0) ? cout << "Дробь равна 0." << endl :
			(this->whole != 0 && this->numerator == 0) ? cout << "Дробь:\t\t" << this->whole << endl :
			(this->whole == 0 && this->numerator != 0) ? cout << "Дробь:\t\t" << this->numerator << " / " << this->denominator << endl :
			cout << "Дробь:\t\t" << this->whole << "   " << this->numerator << " / " << this->denominator << endl;
	}

	void mixed_number()				//Перевод неправильной дроби в смешанное число
	{
		this->whole += this->numerator / this->denominator;
		if (this->numerator < 0) this->numerator *= (-1);
		(this->numerator % this->denominator == 0) ? this->numerator = 0 : this->numerator %= this->denominator;
	}

	void incorrect_fraction()		//Перевод смешанного числа в неправильную дробь
	{
		this->numerator = this->whole * this->denominator + this->numerator;
		this->whole = 0;
	}

	void reduction()				//Сокращение дроби
	{
		if (this->denominator < 0)
		{
			this->denominator *= (-1);
			this->numerator *= (-1);
		}
		int common_divisor = 1, min = 0;
		(abs(this->numerator) <= abs(this->denominator)) ? min = abs(numerator) : min = abs(denominator);
		for (int i = 1; i <= min; i++)
		{
			if (this->numerator % i == 0 && this->denominator % i == 0) common_divisor = i;
		}
		this->numerator /= common_divisor;
		this->denominator /= common_divisor;
	}

	void FractionRand()	//Заполнение элементов дроби случаными числами
	{
		this->numerator = rand() % 100;
		do this->denominator = rand() % 100; while (this->denominator == 0);
		reduction();
	}
};

Fraction operator+(Fraction& left, Fraction& right)
{
	Fraction result;
	if (left.get_whole() != 0) left.incorrect_fraction();
	if (right.get_whole() != 0) right.incorrect_fraction();
	result.set_num(left.get_num() * right.get_denom() + right.get_num() * left.get_denom());
	result.set_denom(left.get_denom() * right.get_denom());
	result.reduction();
	return result;
}

Fraction operator-(Fraction& left, Fraction& right)
{
	Fraction result;
	if (left.get_whole() != 0) left.incorrect_fraction();
	if (right.get_whole() != 0) right.incorrect_fraction();
	result.set_num(left.get_num() * right.get_denom() - right.get_num() * left.get_denom());
	result.set_denom(left.get_denom() * right.get_denom());
	result.reduction();
	return result;
}

Fraction operator*(Fraction& left, Fraction& right)
{
	Fraction result;
	if (left.get_whole() != 0) left.incorrect_fraction();
	if (right.get_whole() != 0) right.incorrect_fraction();
	result.set_num(left.get_num() * right.get_num());
	result.set_denom(left.get_denom() * right.get_denom());
	result.reduction();
	return result;
}

Fraction operator/(Fraction& left, Fraction& right)
{
	Fraction result;
	if (left.get_whole() != 0) left.incorrect_fraction();
	if (right.get_whole() != 0) right.incorrect_fraction();
	result.set_num(left.get_num() * right.get_denom());
	result.set_denom(left.get_denom() * right.get_num());
	result.reduction();
	return result;
}

bool operator==(Fraction& left, Fraction& right)
{
	if (left.get_whole() != 0) left.incorrect_fraction();
	if (right.get_whole() != 0) right.incorrect_fraction();
	return (left.get_num() == right.get_num() && left.get_denom() == right.get_denom()) ? true : false;
}

bool operator!=(Fraction& left, Fraction& right)
{
	return (left == right) ? false : true;
}

bool operator>(Fraction& left, Fraction& right)
{
	if (left.get_whole() != 0) left.incorrect_fraction();
	if (right.get_whole() != 0) right.incorrect_fraction();
	return (double(left.get_num() / left.get_denom()) > double(right.get_num() / right.get_denom())) ? true : false;
}

bool operator<(Fraction& left, Fraction& right)
{
	return (left > right) ? false : true;
}

bool operator>=(Fraction& left, Fraction& right)
{
	return (left > right || left == right) ? true : false;
}

bool operator<=(Fraction& left, Fraction& right)
{
	return (left >= right) ? false : true;
}

void main()
{
	setlocale(LC_ALL, "");
	int num1, num2, denom1, denom2;
	cout << "Первая дробь: " << endl;
	cin >> num1;
	cout << "---" << endl;
	cin >> denom1;
	cout << "Вторая дробь: " << endl;
	cin >> num2;
	cout << "---" << endl;
	cin >> denom2;

	try
	{
	Fraction F1(num1, denom1);
	Fraction F2(num2, denom2);

	cout << "Первая дробь: "; F1.print();
	cout << "Вторая дробь: "; F2.print();
	cout << delimiter;

	cout << "Унарный минус: "; (-F1).print();
	-F1;
	cout << delimiter;

	cout << "Сравнение дробей" << endl;
	cout << "Первая дробь: "; F1.print();
	cout << "Вторая дробь: "; F2.print();
	cout << delimiter;
	(F1 == F2) ? cout << "Дроби равны." << endl : cout << "Дроби не равны." << endl;
	(F1 != F2) ? cout << "Дроби не равны." << endl : cout << "Дроби равны." << endl;
	(F1 < F2) && (F2 > F1) ? cout << "Первая дробь меньше второй." << endl : cout << "Первая дробь больше второй." << endl;
	(F1 <= F2) && (F2 >= F1) ? cout << "Первая дробь не больше второй." << endl : cout << "Первая дробь не меньше второй." << endl;
	cout << delimiter;

	cout << "Арифметические действия над дробями" << endl;
	cout << "Первая дробь: "; F1.print();
	cout << "Вторая дробь: "; F2.print();
	cout << delimiter;
	cout << "Сумма дробей: "; (F1 + F2).print();
	cout << "Разность дробей: "; (F1 - F2).print();
	cout << "Произведение дробей: "; (F1 * F2).print();
	cout << "Частное дробей: "; (F1 / F2).print();
	cout << "Префиксный инкремент: "; (++F1).print();
	cout << "Префиксный декремент: "; (--F1).print();
	cout << "Постфиксный инкремент: "; (F2++).print();
	cout << "Постфиксный декремент: "; (F2--).print();
	cout << delimiter;

	cout << "Составные присваивания" << endl;
	cout << "Первая дробь: "; F1.print();
	cout << "Вторая дробь: "; F2.print();
	cout << delimiter;
	cout << "Составное сложение: "; (F2 += F1).print();
	cout << "Составное вычитание: "; (F2 -= F1).print();
	cout << "Составное умножение: "; (F2 *= F1).print();
	cout << "Составное деление: "; (F2 /= F1).print();
	cout << delimiter;
	}
	catch (const char* e)
	{
		cout << e << endl;
	}
}