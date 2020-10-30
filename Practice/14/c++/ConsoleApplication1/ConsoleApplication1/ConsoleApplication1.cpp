#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int n, a, x;
	cout << "Введите целое число: ";
	cin >> n;
	a = 0;
	x = 1;
	while (x <= n){
		x *= 2;
		a += 1;
	}
	cout << a << '\n';
}
