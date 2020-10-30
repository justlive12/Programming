from math import sqrt

a = float(input('Введите a = '))
b = float(input('Введите b = '))
c = float(input('Введите c = '))
if a == 0:
    print(f'x = {-c / b}')
    quit()
d = b ** 2 - 4 * a * c
if d > 0:
    print(f'x1 = {(-b - sqrt(d)) / (2 * a)}')
    print(f'x2 = {(-b + sqrt(d)) / (2 * a)}')
elif d == 0:
    print(f'x = {-b / (2 * a)}')
else:
    print('Действительных корней нет')