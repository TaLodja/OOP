#include <iostream>
//#include <cmath>
using namespace std;

#define delimiter "\n--------------------------------------\n"

//#define DISTANCE_CHECK
//#define CONSTRUCTORS_CHECK
//#define ASSIGMENT_CHECK


class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this-> x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}

	Point(int x)
	{
		this->x = x;
		this->y = 0;
		cout << "Constructor:\t\t" << this << endl;
	}*/

	Point(double x=0, double y=0)
	{
		this->x = x;
		(*this).y = y;
		cout << "Constructor:\t\t" << this << endl;
	}

	Point(const Point& other)
	{
		// this  - этот объект
		// other - тот объект
		this ->x = other.x;
		this ->y = other.y;
		cout << "CopyConstructor:\t\t" << this << endl;
	}
	 
	//Point(const Point& other) = delete;	//Удаляем контструктор копирования, и таким образом запрещаем копирование объектов
	//Destructor
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//Operators
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Point& operator++()
	{
		this->x++;
		this->y++;
		return *this;
	}

	//Methods
	double distance(const Point& other)const //other - точка, до коорой находим расстояние
	{
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
			//sqrt - Square Root
		return distance;
	}

	void print()const
	{
		cout << "X = " << get_x() << "\tY = " << get_y() << endl;
	}
};

double distance(const Point& A, const Point& B)
{
	//B.set_y(
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	return sqrt(x_distance * x_distance + y_distance * y_distance);
}

Point operator+(const Point& left, const Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	return result;
}

//#define STRUCT_POINT

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRUCT_POINT
	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Объявление переменной 'A' типа 'Point'
	//Создание объекта ‘A’ структуры ‘Point’
	//Создание экземпляра ‘A’ структуры ‘Point’

	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;  //Создание указателя объекта
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT


#ifdef DISTANCE_CHECK
	Point A(2, 3);
	Point B(7, 8);
	A.print();
	B.print();

	cout << delimiter << endl;
	cout << "Расстояние от точки 'A' до точки 'B': " << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'B' до точки 'A': " << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'A' и 'B': " << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'B' и 'A': " << distance(B, A) << endl;
	cout << delimiter << endl;
	cout << sizeof(Point) << endl;

	//Решение дома
	//cout << endl;
	//cout << "Определение расстояния до указанной точки" << endl;
	//cout << "Расстояние до указанной точки: " << A.distance(C) << endl; //т.С - заданная точка; т.А - указанная точка

	//cout << endl;
	//cout << "Определение расстояние между двумя точками" << endl;
	//cout << "Расстояние между двумя точками: "<<distance(A, C) << endl;

#endif // DISTANCE_CHECK

#ifdef CONSTRUCTORS_CHECK
	Point A;
	//A.set_x(2);
	//A.set_y(3);
	//cout << A.get_x() << "\t" << A.get_y() << endl;
	A.print();

	Point B = 5;
	//cout << B.get_x() << "\t" << B.get_y() << endl;
	B.print();

	Point C(7, 8);
	C.print();

	Point D = C;	//CopyConstructor
	D.print();

	Point E;		//Default Constructor
	E = D;			//CopyAssignment
	E.print();

	/*int a = 2;
	int b = 3;
	a = b;
	cout << a << endl;*/

#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	//Point(2, 3); // Здесь мы явно вызываем конструктор, и таким образом создаем временный безымянный объект
	cout << Point(2, 3).distance(Point(7, 8)) << endl;
	//Временные безымянные объекты существуют только в пределах одного выражения
	//Они удаляются из памяти после того, как выражение выполнилось.

	Point A, B, C;

	A = B = C = Point(2, 3);

	A.print();
	B.print();
	C.print();
#endif // ASSIGMENT_CHECK

	Point A(2, 3);
	Point B(4,5);
	Point C = A + B;
	C.print();

	for (Point i(2, 3); i.get_x() < 10; ++i)
	{
		i.print();
	}
}