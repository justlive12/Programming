#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime> 

using namespace std;

int guess_num(){
	int r_num, i = 5, user_num, restart;
	srand(time(NULL));
	r_num = rand() % 101;
	cout << "Здравствуйте! Загадано число от 1 до 100. Угадайте его с пяти попыток. \n";
	while (i > 0) {
		cout << "Введите число: ";
		cin >> user_num;
		if (user_num < r_num) cout << "Загаданное число больше \n";
		else if (user_num > r_num) cout << "Загаданное число меньше \n";
		else {
			cout << "Поздравляю! Вы угадали \n";
			cout << "Хотите начать сначала? (1 - ДА )";
			cin >> restart;
			return restart;
		}
		i -= 1;
	}
	cout << "Вы проиграли. Было загадано: " << r_num << '\n';
	cout << "Хотите начать сначала? (1 - ДА )";
	cin >> restart;
	return restart;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int a = guess_num();
	while (a == 1) {
		a = guess_num();
	}
}
