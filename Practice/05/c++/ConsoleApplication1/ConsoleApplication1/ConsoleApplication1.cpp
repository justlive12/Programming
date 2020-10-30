#include "pch.h"
#include <iostream>

int main() {
	double v0, x0, t, a = 9.8, result;

	std::cin >> x0 >> v0 >> t;
	result = x0 + v0 * t - a * t * t / 2;
	std::cout << "x(t) = " << abs(x0 - result) << "\n";
}
