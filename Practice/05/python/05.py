x0, v0, t = map(int, input(': ').split())
a = 9.8
print(abs(x0 - (x0 + v0 * t - a * t * t / 2)))