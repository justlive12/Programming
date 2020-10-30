quantity = int(input('Введите количество билетов: '))
bank_tickets = [i for i in input('Введите номера билетов: ').split()]
Sigismund = 'a55661'
num = 0
for bank_ticket in bank_tickets:
    short_ticket = bank_ticket[0] + bank_ticket[4:]
    if short_ticket == Sigismund:
        print(bank_ticket)
        num += 1
if num == 0:
    print(-1)