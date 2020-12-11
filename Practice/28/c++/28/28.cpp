#include <iostream>
#include <map>

using namespace std;
typedef map<int, int> new_Map;

void print_factorization(const new_Map& factors) {
	int len_factors = factors.size();
	int i = 0;
	for (auto item : factors) {
		i++;
		cout << item.first;
		if (item.second > 1) {
			cout << "^" << item.second;
		}
		if (i != len_factors) {
			cout << " * ";
		}
	}
}

void factorization(unsigned int num)
{
	new_Map factors;
	while (num > 1){
		for (int i = 2; i <= num; i++) {
			if (num % i == 0) {
				num /= i;
				factors[i] = factors[i] + 1;
				break;
			}
		}
	}
	print_factorization(factors);
}

int main()
{
	setlocale(LC_ALL, "ru");
	int num;
	cout << "Введите число: ";
	cin >> num;
	factorization(num);
}

