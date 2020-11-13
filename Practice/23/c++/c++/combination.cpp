#include "pch.h"
#include "combination.h"
#include "factorial.h"

int get_combination(int k, int n)
{
	return factorial(n) / (factorial(k)*factorial(n - k));
}
