#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int quantity, num;
	string bank_tickets, sigismund, short_ticket, bank_ticket;
	string sep = " ";
	size_t sep_size = sep.size();

	cout << "Введите количество билетов: ";
	cin >> quantity;

	cout << "Введите номера билетов: ";
	cin.ignore();

	getline(cin, bank_tickets);
	sigismund = "a55661";
	num = 0;
	
	while (true) {
		bank_ticket = bank_tickets.substr(0, bank_tickets.find(sep));
		if (bank_ticket.size() != 0) {
			short_ticket = bank_ticket[0] + bank_ticket.substr(4);
			if (short_ticket == sigismund) {
				cout << bank_ticket << '\n';
				num++;
			}
		}
		if (bank_ticket.size() == bank_tickets.size()) {
			break;
		}
		else {
			bank_tickets = bank_tickets.substr(bank_ticket.size() + sep_size);
		}
	}
	if (num == 0) cout << -1;
	return 0;
}
