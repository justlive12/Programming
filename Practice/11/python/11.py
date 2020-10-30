a = float(input('Введите число: '))
b = int(input('Введите степень: '))
i = 0
c = 1
while i < b:
    c *= a
    i += 1
print(c)