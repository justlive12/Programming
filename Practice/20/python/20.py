class Drink:
    def __init__(self):
        self.price = 0.0
        self.volume = 0.0
        self.name = ""

budget = int(input('Сколько у вас денег: '))
number_of_species = int(input('Количество видов: '))

best_product = Drink()
input_info = Drink()

for i in range(number_of_species):
    name, price, volume = input('Введите название, цену и объем: ').split()
    input_info.name = name
    input_info.price = int(price)
    input_info.volume = int(volume)

    liters = (budget // input_info.price) * input_info.volume
    if best_product.volume < liters:
        best_product.volume = liters
        best_product.name = name
        best_product.price = input_info.price
        bottles = int(best_product.volume / input_info.volume)

print(best_product.name, bottles)
print(best_product.volume)
print(budget - (bottles * best_product.price))