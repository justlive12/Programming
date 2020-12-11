n = int(input('Введите количество сигналов: '))
signals = map(int, input('Введите сигналы, через пробел: ').split())

signals_list = []

for signal in signals:
    for i in range(6):
        if i >= len(signals_list):
            break

        if signal > signals_list[i]:
            signals_list.insert(i, signal)
            break

    if i == 5 or i == len(signals_list):
        signals_list.append(signal)

    if len(signals_list) > 5:
        signals_list.pop(0)

    for s in signals_list:
        print(s, end=' ')
    print()
