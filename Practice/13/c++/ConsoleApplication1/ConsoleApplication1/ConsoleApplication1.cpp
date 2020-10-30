#include "pch.h"
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int n, i, limit;
	cout << "Введите число: ";
	cin >> n;
	if (n == 2) {
		cout << "Простое";
		exit(1);
	}
	limit = (int)sqrt(n);
	for (i = 2; i <= limit; i++) {
		if (n % i == 0) {
			cout << "Составное";
			exit(1);
		}
	}
	cout << "Простое";
}
