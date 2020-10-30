#include "pch.h"
#include <iostream>
#include <string>
#include <map>
#include <math.h>
#include <sstream>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	stringstream container;
	int num, str_size, pow_lis, lr;
	string str;
	cout << "Введите длину пароля: ";
	cin >> num;
	cout << "Введите последовательность букв: ";
	cin >> str;

	str_size = str.length();
	string *k = new string[str_size];
	for (int i = 0; i < str_size; i++) {
		k[i] = str[i];
	}

	pow_lis = pow(str_size, num);
	int *lis = new int[pow_lis];
	for (int i = 0; i < pow_lis; i++) {
		lis[i] = i;
	}

	string *num_el = new string[str_size];
	for (int i = 0; i < str_size; i++) {
		num_el[i] = to_string(i);
	}

	string *lis_str = new string[pow_lis];

	for (int i = 0; i < pow_lis; i++) {
		int el_lis = lis[i];
		string ser = "", res;
		while (el_lis != 0) {
			ser += to_string(el_lis % str_size);
			el_lis /= str_size;
		}
		for (int i = ser.length() - 1; i >= 0; i--) {
			res += ser[i];
		}
		lr = res.length();
		if (lr != num) {
			string res_lr;
			for (int i = 0; i < num - lr; i++) {
				res_lr += "0";
			}
			res = res_lr + res;
		}
		lis_str[i] = res;
	}
	
	for (int i = 0; i < pow_lis; i++) {
		int kr = 1;
		string lis_i = lis_str[i];
		for (int j = 0; j < str_size; j++) {
			if (lis_i.find(to_string(j)) != string::npos) kr *= 1;
			else kr *= 0;
		}
		if (kr == 1) {
			string res = "";
			for (int i = 0; i < str_size; i++) {
				container << lis_i[i];
				int a;
				container >> a;
				container.clear();
				res += k[a];
			}
			cout << res << " ";
		}
	}

	return 0;
}