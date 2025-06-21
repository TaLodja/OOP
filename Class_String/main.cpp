#include <iostream>
using namespace std;

#define delimiter "\n----------------------------------\n"

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Указатель на строку в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	//Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char str[])
	{
		while(str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++) this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i<size; i++) this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	~String()
	{
		if (str!=nullptr) delete[] str;
		this->str = nullptr;
		this->size = 0;
		cout << "Destructor:\t\t" << this << endl;
	}

	//Operatprs:
	String& operator=(const String& other)
	{
		if (this == &other) return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++) this->str[i] = other.str[i];
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//Methods:
	void info()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

void main()
{
	setlocale(LC_ALL, "");
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
}