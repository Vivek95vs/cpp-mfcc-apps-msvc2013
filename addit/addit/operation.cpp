#include "operation.h"
#include "iostream"
#include "conio.h"
using namespace std;


operation::operation()
{
}


operation::~operation()
{
}

float operation::add()
{
	float a, b = 4, c = 9;

	a = b + c;

	cout << "the value is" << a;

	return a;
}
