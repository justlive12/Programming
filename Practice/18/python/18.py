from collections import Counter

string = 'hallo, klempner, das, ist, fantastisch, fluggegecheimen'
letters = [i for i in string if i.isalpha()]
letters_len = len(letters)
letters = dict(Counter(letters))

probability = 1

stop_word = list(input('Введите стоп слово: '))

for i in stop_word:
    probability *= (letters[i] / letters_len)

print(probability)