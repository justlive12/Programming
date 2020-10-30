#include "pch.h"
#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	int s, l1, r1, l2, r2;

	cout << "Введите целое число, затем два диапазона целых чисел: " << endl;
	cin >> s >> l1 >> r1 >> l2 >> r2;

	bool success = true;
	int x1 = l1;
	int x2;

	if (x1 + r2 < s) {
		x2 = r2;

		if (s > r1 + x2) {
			cout << -1 << endl;
			success = false;
		}
		else {
			x1 = s - r2;
		}
	}
	else {
		if (s < l1 + l2) {
			cout << -1 << endl;
			success = false;
		}
		else {
			x2 = s - x1;
		}
	}

	if (success) {
		cout << x1 << " " << x2;
	}
}
