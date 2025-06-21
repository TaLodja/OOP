#include <iostream>
using namespace std;

class A {
	int* a;
public:
	A(int x)
	{
		a = new int(x);
		cout << "A(" << x << ")\n";
	}
	~A()
	{
		delete a;
		cout << "~A()\n";
	}
};
A f()
{
	A a1(123);
	return a1;
}
void main() {
	f();
}
