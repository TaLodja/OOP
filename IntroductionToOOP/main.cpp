#include <iostream>
//#include <cmath>
using namespace std;

//#define CONSTRUCTORS_CHECK
#define DISTANCE_CHECK

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
	//Destructor
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//Methods

	// Разбор в классе
	double distance(Point other) //other - точка, до коорой находим расстояние
	{
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
			//sqrt - Square Root
		return distance;
	}

	// Мой вариант
	/*double distance(Point Point)const
	{
		double x1 = Point.x;
		double y1 = Point.y;
		return sqrt(pow(get_x() - x1, 2) + pow(get_y() - y1, 2));
	}*/

	void print()const
	{
		cout << "X = " << get_x() << "\tY = " << get_y() << endl;
	}
};

//Решение в классе

double distance(Point A, Point B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	return sqrt(x_distance * x_distance + y_distance * y_distance);
}

//Решение дома
//double distance(Point Point1, Point Point2)
//{
//	double x1 = Point1.get_x();
//	double x2 = Point2.get_x();
//	double y1 = Point1.get_y();
//	double y2 = Point2.get_y();
//	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//}

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
#endif // CONSTRUCTORS_CHECK

	Point A(2, 3);
	Point B(7, 8);
	A.print();
	B.print();

	cout << "Расстояние от точки 'A' до точки 'B': " << A.distance(B) << endl;
	cout << "Расстояние от точки 'B' до точки 'A': " << B.distance(A) << endl;

	cout << "Расстояние между точками 'A' и 'B': " << distance(A, B) << endl;
	cout << "Расстояние между точками 'B' и 'A': " << distance(B, A) << endl;
	
	//Решение дома
	//cout << endl;
	//cout << "Определение расстояния до указанной точки" << endl;
	//cout << "Расстояние до указанной точки: " << A.distance(C) << endl; //т.С - заданная точка; т.А - указанная точка

	//cout << endl;
	//cout << "Определение расстояние между двумя точками" << endl;
	//cout << "Расстояние между двумя точками: "<<distance(A, C) << endl;

}