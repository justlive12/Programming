#include "pch.h"
#include <iostream>

int main()
{
	int a, b;
	std::cin >> a >> b;
    std::cout << "a+b=" << a + b << "\n" << "a-b=" << a - b << "\n" << "a*b=" << a * b << "\n" << "a/b=" << a / b << '\n' << "\n";
	double a1, b1;
	std::cin >> a1 >> b1;
	std::cout << "double + double = " << a1 + b1 << "\n" << "double - double = " << a1 - b1 << "\n" << "double * double = " << a1 * b1 << "\n" << "double / double = " << a1 / b1 << "\n" << "\n";
	std::cout << "double + int = " << a1 + b << "\n" << "double - int = " << a1 - b << "\n" << "double * int = " << a1 * b << "\n" << "double / int = " << a1 / b << '\n' << "\n";
	std::cout << "int + double = " << a + b1 << "\n" << "int - double = " << a - b1 << "\n" << "int * double = " << a * b1 << "\n" << "int / double = " << a / b1 << '\n';

}
