a = input('a = ')
b = input('b = ')

c = a
a = b
b = c
print('первый способ: ', f'a = {a}, b = {b}')

a, b = b, a
print('второй способ', f'a = {a}, b = {b}')