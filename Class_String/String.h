#pragma once
#include <Windows.h>		//Для вывода строки на русском
#include <iostream>

#define delimiter "\n----------------------------------\n"

//////////////////////////////////////////////////////////
//			Объявление класса - Class declaration		//

class String;
String operator+(const String& left, const String& right);
std::ostream& operator<<(std::ostream& os, const String& obj);
std::istream& operator>>(std::istream& is, String& obj);
std::istream& getline(std::istream& is, String& obj);

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
	String& operator+=(const String& other);
	char operator[](int i)const;
	char& operator[](int i);

	//Methods:
	void info()const;
};

//			Конец объявления класса - Class declaration	end		//
//////////////////////////////////////////////////////////////////