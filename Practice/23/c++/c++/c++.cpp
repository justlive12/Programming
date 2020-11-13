#include "pch.h"
#include <iostream>
#include <iomanip>
#include "factorial.h"
#include "sinus.h";
#include "combination.h"

using namespace std;
const double PI = 3.141592653589793;

int main()
{
	cout << "n" << "\t" << "n!" << endl;
	for (int i = 1; i < 11; i++) {
		cout << i << "\t" << factorial(i) << endl;
	}
	cout << endl;

	cout << "x" << "\t" << "sin(x)" << endl;
	for (float i = 0; i <= 0.7854; i += PI / 180) {
		cout << setprecision(4) << i << "\t" << sinus(i, 5) << endl;
	}
	cout << endl;

	cout << "k" << "\t" << "C(k, 10)" << endl;
	for (int i = 1; i < 11; i++) {
		cout << i << "\t" << get_combination(i, 10) << endl;
	}
}

