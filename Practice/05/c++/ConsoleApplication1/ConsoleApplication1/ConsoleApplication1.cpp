#include "pch.h"
#include <iostream>

int main()
{
	double v0, x0, t, a = 9.8;
	std::cin >> x0 >> v0 >> t;
	std::cout << "x(t) = " << x0 + v0 * t - a * t*t / 2 << "\n";
	std::cout << "x(t) = " << x0 + v0 * t - 1/2 * a * t*t << "\n";
}


