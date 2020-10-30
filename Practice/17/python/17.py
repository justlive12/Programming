from collections import Counter

li = list(range(37))
n = []
red_list = [1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36]
red = 0
black = 0
k = 12


def get_probability(i):
    n.append(i)
    c = Counter(n)
    a = [k for k, v in c.items() if v == max(c.values())]
    for i in a:
        print(i, end=' ')
    print()
    return a


while True:
    num = int(input(': '))
    if k > 0 and num in li:
        li.remove(num)
    elif k == 0:
        li = list(range(37))
        li.remove(num)
        k = 12
    k -= 1

    if num < 0:
        quit()
    if num in red_list:
        red += 1
    elif num != 0:
        black += 1

    nums = get_probability(num)

    for i in li:
        print(i, end=' ')
    print()
    print(red, black)