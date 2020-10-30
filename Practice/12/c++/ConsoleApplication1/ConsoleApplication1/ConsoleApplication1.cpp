#include "pch.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int n, i, fac = 2;
	cout << "Введите число: ";
	cin >> n;
	if (n == 1 || n == 2) {
		cout << n;
		exit(1);
	}
	for (i = 3; i <= n; i++) {
		fac *= i;
	}
	cout << fac;
}
