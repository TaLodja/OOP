#include "String.h"
using std::cin;
using std::cout;
using std::endl;

/// ------------------------------------------------------------///

//////////////////////////////////////////////////////////
//			Определение класса - Class definition		//

int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
//Constructors:
//Ключевое слово 'explicit' можно использовать только внутри класса
String::String(int size) : size(size), str(new char[size] {})
{
	cout << "DefaultConstructor:\t" << this << endl;
}
//	:: - Scope operator (Оператор разрешения видимости)
String::String(const char str[]) :String(strlen(str) + 1)
{
	for (int i = 0; str[i]; i++) this->str[i] = str[i];
	cout << "Constructor:\t\t" << this << endl;
}
String::String(const String& other) : String(other.str)
{
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other) : size(other.size), str(other.str)
{
	//this->size = other.size;
	//this->str = other.str;
	other.size = 0;
	other.str = nullptr;		//Защищаем память от удаления деструктором.
	cout << "MoveConstructor\t\t" << this << endl;
}
String::~String()
{
	delete[] str;
	this->str = nullptr;
	this->size = 0;
	cout << "Destructor:\t\t" << this << endl;
}

//Operatprs:
String& String::operator=(const String& other)
{
	if (this == &other) return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++) this->str[i] = other.str[i];
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

String& String::operator=(String&& other)
{
	if (this == &other) return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.size = 0;
	other.str = nullptr;  //Защизаем динамическую память от удаления в деструкторе
	cout << "MoveAssignment:\t\t" << this << endl;
	return *this;
}

String& String::operator+=(const String& other)
{
	return *this = *this + other;
}

char String::operator[](int i)const
{
	return str[i];
}

char& String::operator[](int i)
{
	return str[i];
}

//Methods:
void String::info()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);		//Default constructor
	for (int i = 0; left[i]; i++)
		result[i] = left[i];
	for (int i = 0; right[i]; i++)
		result[i + left.get_size() - 1] = right[i];
	cout << "Operator+" << endl;
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

std::istream& operator>>(std::istream& is, String& obj)
{
	const int SIZE = 1024; //Размер буфера - 1 kВ
	char buffer[SIZE] = {};
	is >> buffer;
	//is.getline(buffer, SIZE);
	obj = buffer;
	return is;
	/*const int SIZE = 32;
	char sz_input[SIZE] = {};
	is.getline(sz_input, SIZE);
	String temp(sz_input);
	obj= temp;
	return is;*/
}

std::istream& getline(std::istream& is, String& obj)
{
	is.getline(obj.get_str(), obj.get_size());
	return is;
}

//			Конец определения класса - Class definition	end		//
//////////////////////////////////////////////////////////////////
