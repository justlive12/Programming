from math import *
from random import randrange


def is_sorted(array, direction=True):
    array_len = len(array)
    if direction:
        for i in range(1, array_len):
            if array[i - 1] > array[i]:
                return False
    else:
        for i in range(1, array_len):
            if array[i - 1] < array[i]:
                return False
    return True


def BozoSort(array, direction=True):
    new_array = []

    if isinstance(array[0], list):
        for li in array:
            new_array.extend(li)
    else:
        new_array = array.copy()

    len_new_array = len(new_array)
    while not is_sorted(new_array, direction):
        first, second = randrange(len_new_array), randrange(len_new_array)
        new_array[first], new_array[second] = new_array[second], new_array[first]
    return new_array


length = int(input('Введите число из которого можно извлечь квадратный корень: '))
sqrt_len = sqrt(length)
one_dimensional_list = [int(i) for i in input('Введите элементы массива через пробел: ').split()]

two_dimensional_list = []
li = []
i = 0

for element in one_dimensional_list:
    li.append(element)
    i += 1
    if i == sqrt_len:
        two_dimensional_list.append(li)
        i = 0
        li = []
del li, i

amount_of_elements = 3
three_elements = []
for i in range(amount_of_elements):
    three_elements.append(one_dimensional_list[i])

print(' '.join(map(str, BozoSort(one_dimensional_list, True))))
print(' '.join(map(str, BozoSort(one_dimensional_list, False))))
print(' '.join(map(str, BozoSort(two_dimensional_list, True))))
print(' '.join(map(str, BozoSort(two_dimensional_list, False))))
print(' '.join(map(str, BozoSort(three_elements, True))))
print(' '.join(map(str, BozoSort(three_elements, False))))
