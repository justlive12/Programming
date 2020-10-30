#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

struct Drink {
	string name;
	long long   price;
	long long   volume;
};

int main()
{
	setlocale(LC_ALL, "ru");

	int budget, number_of_species;
	cout << "Сколько у вас денег: ";
	cin >> budget;
	cout << "Количество видов: ";
	cin >> number_of_species;

	Drink best_product;
	Drink input_info;
	for (int i = 0; i < number_of_species; ++i) {
		cout << "Введите название, цену и объем: ";
		cin >> input_info.name >> input_info.price >> input_info.volume;

		int liters = (budget / input_info.price) * input_info.volume;

		if (liters == 0)
			continue;

		if (best_product.price == 0) {
			best_product = input_info;
			continue;
		}

		int best_liters = (budget / best_product.price) * best_product.volume;

		if (liters > best_liters)
			best_product = input_info;
	}

	if (best_product.price == 0) cout << -1 << endl;
	else {
		int bottles = budget / best_product.price;
		cout << best_product.name << " " << bottles << "\n"
			<< bottles * best_product.volume << "\n"
			<< budget - best_product.price * bottles << endl;
	}
}
