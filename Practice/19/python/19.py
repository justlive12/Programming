from itertools import *

num = int(input('Введите число: '))
letters = input('Введите последовательность букв: ')
letters_len = len(letters)

def equal(letters):
    sum = 0
    for i in permutations(letters):
        for j in i:
            print(j, end='')
        print(end=' ')
        sum += 1
    print()
    print(sum)

def not_equal(letters, letters_len):
    sum = 0
    for i in permutations(letters, num):
        print(i)

if num == letters_len:
    equal(letters)
elif num != letters_len:
    not_equal(letters, num)