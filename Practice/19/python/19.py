from itertools import *
num = int(input('Введите число: '))
letters = input('Введите последовательность букв: ')
letters_len = len(letters)

def equal(letters):
    sum = 0
    for i in permutations(letters):
        print(''.join(i), end=' ')
    print()

def not_equal(letters, letters_len, num):
    arr = []
    arr2 = set()
    b = 0
    for item in combinations_with_replacement(letters, num):
        xx = ''.join(item)
        for i in letters:
            if i in xx:
                b += 1
        if b == letters_len:
            for a in permutations(xx):
                arr2.add(''.join(a))
        b = 0
    for i in arr2:
        a = 0
        print(i, end=' ')
        if a == 100:
            print()
            a = 0
        a += 1

if num == letters_len:
    equal(letters)
elif num != letters_len:
    not_equal(letters, letters_len, num)