#include <iostream>
using namespace std;

#define delimiter "\n---------------------------------------\n"

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
	void set_string(char string[])
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
		this->str[length] = '\0';
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const char string[])
	{
		for (int i = 0; string[i] != '\0'; i++)
		{
			this->length++;
		}
		this->str = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			this->str[i] = string[i];
		}
		cout << "Constructor:\t\t" << this << endl;
		this->str[length] = '\0';
	}
	String(const String& other)
	{
		this->length = other.length;
		this->str = new char[other.length + 1];
		for (int i = 0; i <= other.length; i++)
		{
			this->str[i] = other.str[i];
		}
		cout << "CopyConstructor:\t" << this << endl;
	}

	//Destructor
	~String()
	{
		if (str != nullptr) delete[] str;
		cout << "Destructor:\t\t" << this << endl;
	}

	//Operators
	String& operator=(const String& other)
	{
		this->length = other.length;
		this->str = new char[other.length + 1];
		for (int i = 0; i <= other.length; i++)
		{
			this->str[i] = other.str[i];
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//Methods
	void print()const
	{
		for (int i = 0; i <= length; i++)
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
		temp[i] = right.get_string()[i - left.get_length()];
	}
	result.set_string(temp);
	delete[] temp;
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

//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str;						//DefaultConstructors
	String str2(10);				//Constructors
	String str3("Happy Birthday!");	//Constructor
	String str4 = str3;				//CopyConstructor
	str = str4;						//CopyAssignment
	cout << str << endl;
	cout << str2 << endl;
	cout << str3 << endl;
	cout << str4 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	String A, B, C = "Hello, World!";
	cout << delimiter;
	A = B = C;
	cout << delimiter;
	A.print();
	B.print();
	C.print();
#endif // ASSIGNMENT_CHECK
	
	string str1 = "Hello";
	string str2 = "World";
	string str3 = str1 + str2;
	cout << str3 << endl;
}