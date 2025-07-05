#include "String.h"
using std::cin;
using std::cout;
using std::endl;

//#define CONSTRUCTORS_CHECK
//#define OPERATOR_PLUS
#define ISTREAM_OPERATOR
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
	String str7{ }; //Явный вызов DefaultConstructor.
	//!!!	{} следует использовать с осторожностью		!!!

	String str9 = str3;		//CopyConstructor
	str9.info();
#endif // CALLING_CONSTRUCTORS

}