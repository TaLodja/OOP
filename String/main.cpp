#include <iostream>
using namespace std;

class String
{
	int length;
	char* str;
public:
	int get_length()const
	{
		return length;
	}
	char* get_string()const
	{
		return str;
	}
	void set_length(int length)
	{
		this->length = length;
	}
	void set_string(char* string)
	{
		this->str = new char[get_length() + 1];
		for (int i = 0; i < this->get_length(); i++)
		{
			this->str[i] = string[i];
		}
	}

	//Constructors
	String()
	{
		this->length = 0;
		this->str = nullptr;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(int length)
	{
		this->length = length + 1;
		this->str = new char[length + 1];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const char* string)
	{
		this->length = sizeof(string) + 1;
		this->str = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			this->str[i] = string[i];
		}
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		this->length = other.length;
		this->str = new char[other.length + 1];
		for (int i = 0; i < other.length; i++)
		{
			this->str[i] = other.str[i];
		}
		cout << "CopyConstructor:\t" << this << endl;
	}

	//Destructor
	~String()
	{
		if (str != nullptr) delete[] str;
		str = nullptr;
		cout << "Destructor:\t\t" << this << endl;
	}

	//Operators
	String& operator=(const String& other)
	{
		this->length = other.length;
		this->str = new char[other.length + 1];
		for (int i = 0; i < other.length; i++)
		{
			this->str[i] = other.str[i];
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//Methods
	void print()const
	{
		for (int i = 0; i < length; i++)
		{
			cout << str[i];
		}
		cout << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String result;
	result.set_length(left.get_length() + right.get_length());
	char* temp = new char[result.get_length() + 1];
	for (int i = 0; i < left.get_length(); i++)
	{
		temp[i] = left.get_string()[i];
	}
	for (int i = left.get_length(); i < result.get_length(); i++)
	{
		temp[i] = right.get_string()[i- left.get_length()];
	}
	result.set_string(temp);
	delete[] temp;
	temp = nullptr;
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	for (int i = 0; i < obj.get_length(); i++)
	{
		os << obj.get_string()[i];
	}
	return os;
}

void main()
{
	setlocale(LC_ALL, "");
	String str1 = "Hello";
	String str2 = "World";
	String str3 = str1 + str2;
	cout << str3 << endl;
}