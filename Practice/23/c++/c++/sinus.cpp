#include "pch.h"
#include "sinus.h"
#include "factorial.h"
#include <cmath>

float sinus(float x, int k)
{
	float sin = x - pow(x, 3) / 6;
	if (k == 1) return sin;
	for (int i = 2; i <= k; i++) {
		int n = 2 * i + 1;
		sin = sin + pow(-1, i) * pow(x, n) / factorial(n);
	}
	return sin;
}
