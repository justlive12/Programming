#include "pch.h"
#include "factorial.h"

int factorial(int a) {
	int n = 2;
	if (a == 1 || a == 2) return a;
	else if (a == 0) return 1;
	for (int i = 3; i <= a; i++) {
		n *= i;
	}
	return n;
}
