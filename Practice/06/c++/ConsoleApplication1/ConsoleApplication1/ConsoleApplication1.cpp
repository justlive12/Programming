#include "pch.h"
#include <iostream>
#include <cmath>

using namespace std;

double getValue(char a)
{
	while (true)
	{
		cout << "Введите число " << a << " : ";
		double a;
		cin >> a;

		if (cin.fail()) 
		{
			cin.clear(); 
			cin.ignore(32767, '\n'); 
			cout << "Некорректный ввод данных. Пожалуйста введите число.\n";
		}
		else
		{
			cin.ignore(32767, '\n');
			return a;
		}
	}
}

double printValueEquation(double a, double b, double c) {
	double d, x1, x2;
	if (a == 0) {
		cout << -c / b;
		return 0;
	}
	d = b * b - 4 * a * c;
	if (d > 0) {
		x1 = (-b - sqrt(d)) / (2 * a);
		x2 = (-b + sqrt(d)) / (2 * a);
		cout << "x1 = " << x1 << "\nx2 = " << x2;
	}
	else if (d == 0) {
		x1 = -b / (2 * a);
		cout << "x1 = " << x1;
	}
	else {
		cout << "Нет действительных корней уравнения.";
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	double a, b, c;
	a = getValue('a');
	b = getValue('b');
	c = getValue('c');
	printValueEquation(a, b, c);
}




