#include "pch.h"
#include <iostream>
#include <map>

using namespace std;

int get_array(int arr[]) {
	for (int i = 0; i < 37; i++) {
		arr[i] = i;
	}
	return *arr;
}

int main()
{
	setlocale(LC_ALL, "rus");

	int arr[37], k = 12, num, max = 0;
	int reds = 0, blacks = 0;
	map<int, int> myMap;

	get_array(arr);

	while (true) {
		cout << "Введите число: ";
		cin >> num;
		cout << endl;
		if (num < 0) break;

		if (k > 0 && arr[num] != -1) arr[num] = -1;
		else if (k == 0) {
			get_array(arr);
			arr[num] = -1;
			k = 12;
		}

		k--;

		auto it = myMap.find(num);
		if (it == myMap.end()) {
			myMap.emplace(num, 1);
		}
		else {
			myMap[num]++;
		}

		//определяем максимальное количество повторений числа
		for (auto elem : myMap) {
			if (elem.second > max) max = elem.second;
		}
		//выводим числа выпавшие максимальное число раз
		for (auto elem : myMap) {
			if (elem.second == max) cout << elem.first << ' ';
		}
		cout << endl;

		for (int i = 0; i < 37; i++) {
			if (arr[i] != -1) cout << i << ' ';
		}
		cout << endl;

		//определяем количество черных и красных чисел
		if (num != 0) {
			if (num <= 10 || (num > 18 && num <= 28)) {
				if (num % 2 == 1) ++reds;
				else ++blacks;
			}
			else {
				if (num % 2 == 0) ++reds;
				else ++blacks;
			}
		}

		cout << reds << " " << blacks << endl;
		cout << endl;
	}



}
