#include "pch.h"
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	int a, b, i, c;
	cout << "Введите число: ";
	cin >> a;
	c = a;
	cout << "Введите степень числа: ";
	cin >> b;
	for (i = 1; i < b; i++) {
		c *= a;
	}
	cout << c;
}
