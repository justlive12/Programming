#include "pch.h"
#include <iostream>
using namespace std;

double getValue()
{
	while (true)
	{
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
			return a;
		}
	}
}

char getOperator()
{
	while (true) 
	{
		char sm;
		cin >> sm;
		if (sm == '+' || sm == '-' || sm == '*' || sm == '/') {
			return sm;
		}
		else {
			cin.clear();
			cin.ignore(32767, '\n');
			std::cout << "Некорректный ввод данных. Пожалуйста выберите \"+\", \"-\" \"*\" или \"/\".\n";
		}
	}
}

void printResult(double a, char sm, double b)
{
	switch (sm) {
	case '+':
		cout << a << " + " << b << " = " << a + b << '\n';
		break;
	case '-':
		cout << a << " - " << b << " = " << a - b << '\n';
		break;
	case '*':
		cout << a << " * " << b << " = " << a * b << '\n';
		break;
	case '/':
		cout << a << " / " << b << " = " << a / b << '\n';
		break;
	default:
		cout << "Некорректный ввод данных.";
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	double a = getValue();
	char sm = getOperator();
	double b = getValue();
	printResult(a, sm, b);
	return 0;
}