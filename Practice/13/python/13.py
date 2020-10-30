n = int(input('Введите число: '))
if n < 2 or n > 10**9:
    print('Вводимое число должно быть в пределах от 2 до 10^9 включительно')
    quit()
num = 2
while n % num != 0:
    num += 1
if num != 2:
    print('Простое')
else:
    print('Непростое')