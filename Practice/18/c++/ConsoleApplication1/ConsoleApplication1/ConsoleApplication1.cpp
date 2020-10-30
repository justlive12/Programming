#include "pch.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	double probability = 1;
	int len, len_stop_word, letters_len = 0;
	string str = "hallo, klempner, das, ist, fantastisch, fluggegecheimen";
	string ch, stop_word;
	map<string, int> myMap;

	len = str.size();

	for (int i = 0; i < len; i++) {
		ch = str[i];
		if (isalpha(str[i])) {
			letters_len += 1;
			auto it = myMap.find(ch);
			if (it == myMap.end()) {
				myMap.emplace(ch, 1);
			}
			else {
				myMap[ch]++;
			}
		}
	}

	cout << "Введите стоп слово: ";
	cin >> stop_word;
	
	len_stop_word = stop_word.size();

	for (int i = 0; i < len_stop_word; i++) {
		ch = stop_word[i];
		probability = (probability * ((double)myMap[ch] / letters_len));
	}

	cout << probability;
}

