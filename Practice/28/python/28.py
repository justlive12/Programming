def print_factorization(factors):
    number_of_keys = len(factors.keys())
    i = 0
    for k, v in factors.items():
        i += 1
        print(k, end='')
        if v > 1:
            print(f'^{v}', end='')
        if i != number_of_keys:
            print(' * ', end='')


def factorization(n):
    factors = {}
    while n > 1:
        for i in range(2, n + 1):
            if n % i == 0:
                n //= i
                factors[i] = factors.get(i, 0) + 1
                break
    print_factorization(factors)


num = int(input('Введите число: '))
factorization(num)
