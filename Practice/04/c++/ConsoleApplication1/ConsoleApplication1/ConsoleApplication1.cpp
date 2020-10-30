#include "pch.h"
#include <iostream>

int main()
{
	double a, b, c;
	std::cin >> a >> b;
	c = a;
	a = b;
	b = c;
	std::cout << "a = " << a << " b = " << b << '\n'; 
	a += b;
	b = a - b;
	a = a - b;
	std::cout << "a = " << a << " b = " << b << '\n';
}

