#include <Windows.h>		//Для вывода строки на русском
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n----------------------------------\n"

class String;
String operator+(const String& left, const String& right);

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Указатель на строку в динамической памяти
public:
	int get_size()const;
	const char* get_str()const;
	char* get_str();

	//Constructors:
	explicit String(int size = 80);
	String(const char str[]);
	String(const String& other);
	String(String&& other);
	~String();

	//Operatprs:
	String& operator=(const String& other);
	String& operator=(String&& other);
	char operator[](int i)const;
	char& operator[](int i);
	String& operator+=(const String& other);

	//Methods:
	void info()const;
};
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
	other.size - 0;
	other.str = nullptr;  //Защизаем динамическую память от удаления в деструкторе
	cout << "MoveAssignment:\t\t" << this << endl;
	return *this;
}

char String::operator[](int i)const
{
	return str[i];
}

char& String::operator[](int i)
{
	return str[i];
}

String& String::operator+=(const String& other)
{
	return *this = *this + other;
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

//#define CONSTRUCTORS_CHECK
#define OPERATOR_PLUS
//#define ISTREAM_OPERATOR
//#define CALLING_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str1(5);			//explicit-конструктор нельзя вызвать оператором '=', но всегда можно вызвать при помощи круглых скобок
	str1.info();
	cout << str1 << endl;

	cout << delimiter << endl;

	String str2 = "Hello";
	str2 = str2;
	cout << str2 << endl;

	cout << delimiter << endl;

	String str3 = str2;		//CopyConstructor
	cout << str3 << endl;

	cout << delimiter << endl;

	String str4;
	str4 = str3;
	cout << str4 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATOR_PLUS
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	cout << delimiter << endl;
	String str4 = str3;
	cout << str4 << endl;
	cout << delimiter << endl;
#endif // OPERATOR_PLUS

#ifdef ISTREAM_OPERATOR
	String str;
	cout << "Введите строку: ";
	SetConsoleCP(1251);				//Для вывода строки на русском
	//cin >> str;
	//cin.getline(str.get_str(), str.get_size());
	getline(cin, str);
	SetConsoleCP(866);
	cout << str << endl;
#endif // ISTREAM_OPERATOR



	/*String str1 = "Hello";
	String str2 = "World";
	str1 += str2;
	cout << str1 << endl;*/

#ifdef CALLING_CONSTRUCTORS
	String str1;		//Default constructor
	str1.info();

	String str2(8);		//Single-argument constructor ('int') 8 - размер строки в байтах;
	str2.info();

	String str3 = "Hello";	//Single-argument constructor ('const char*');
	str3.info();
	cout << typeid("Hello").name() << endl;

	String str4();		//Здесь не вызывается никакой конструктор,
	//и не создается никакой объект, здесь происходит
	//объявление функции 'str4()', которая ничего не принимает
	//и возвращает объект типа 'String'.
//Пустые () НЕ делают явный вызов DefaultConstructor.
//str4.info();

//Ксли нужно явно вызвать DefaultConstructor, это можно сделать {}
	String str5(8);	//Создается строка длиной 8 байт
	String str6{ 8 }; //Создается строка длиной 8 байт, т.е. {} вызывают конструктор.
	string str7{ }; //Явный вызов DefaultConstructor.
	//!!!	{} следует использовать с осторожностью		!!!

	String str9 = str3;		//CopyConstructor
	str9.info();
#endif // CALLING_CONSTRUCTORS

}