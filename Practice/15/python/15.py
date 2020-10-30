from random import randint
def guess_num():
    r_num = randint(0, 100)
    print(r_num)
    i = 5
    print('Здравствуйте! Загадано число от 1 до 100. Угадайте его с пяти попыток.')
    while i > 0:
        user_num = input(': ')
        if not user_num.isdigit():
            quit()
        user_num = int(user_num)
        if user_num == '':
            quit()
        elif user_num < r_num:
            print('Загаданное число больше')
        elif user_num > r_num:
            print('Загаданное число меньше')
        elif user_num == r_num:
            print('Поздравляю! Вы угадали')
            print('Хотите начать сначала? (1 - ДА )')
            return input(': ')
        i -= 1
    print(f'Вы проиграли. Было загадано: {r_num}')
    print('Хотите начать сначала? (1 - ДА )')
    return input(': ')
    
while guess_num() == '1':
    continue
else:
    print('Спасибо за игру')